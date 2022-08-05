# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 14th June 2021 6:53:51 pm
# @modified   Friday, 5th August 2022 9:56:13 am
# @project    stm-utils
# @brief      CMake package for stm-utils project
#    
# @note This project should be build with DEVICE flag that determines target device. List of supported MCU's can be found
#    in `cmake/device.cmake` file.
#
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

cmake_minimum_required(VERSION 3.16)

# ====================================================================================================================================
# ------------------------------------------------------ Project Configuration -------------------------------------------------------
# ====================================================================================================================================

# Establish build type
set(MASTER_PROJECT OFF)
if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
  set(MASTER_PROJECT ON)
endif()

# Project name, version and used languages
project(stm-utils VERSION 1.0 LANGUAGES ASM C CXX)

# ====================================================================================================================================
# ------------------------------------------------------------- Options --------------------------------------------------------------
# ====================================================================================================================================

# Target device
set(HAL_BUILD ON CACHE BOOL
    "If true, HAL library is built on top of LL")

# ====================================================================================================================================
# ----------------------------------------------------- Toolchain configuration ------------------------------------------------------
# ====================================================================================================================================

if(${MASTER_PROJECT})

    # Set C standard for all targets
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED True)
    set(CMAKE_C_EXTENSIONS False)

    # Make sure that custom modules like stm-utils-config.cmake.in are found
    list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)
    list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake/templates)

    # Select appropriate device-dependend options
    include(${CMAKE_SOURCE_DIR}/cmake/device.cmake)

endif()

# ====================================================================================================================================
# ------------------------------------------------------- Build configruation --------------------------------------------------------
# ====================================================================================================================================

# Add required defines
add_compile_definitions(
    PUBLIC
        ${DEVICE}
        ${DeviceType}
)

# ====================================================================================================================================
# ------------------------------------------------------------ Components ------------------------------------------------------------
# ====================================================================================================================================

# CMSIS libraries
add_subdirectory(src/cmsis)
# Device-specific CMSIS headers
add_subdirectory(src/device)
# HAL/LL libraries
add_subdirectory(src/hal)

# ====================================================================================================================================
# ------------------------------------------------------ Targets' installation -------------------------------------------------------
# ====================================================================================================================================

if(${MASTER_PROJECT})

    # Include standard isntall paths
    include(GNUInstallDirs)

    # Export the targets to a script
    install(EXPORT ${PROJECT_NAME}-targets
        FILE
            ${PROJECT_NAME}-targets.cmake
        NAMESPACE
            ${PROJECT_NAME}::
        DESTINATION
            ${CMAKE_INSTALL_LIBDIR}
    )

    # Export targets
    export(EXPORT ${PROJECT_NAME}-targets
        FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-targets.cmake
        NAMESPACE ${PROJECT_NAME}::
    )

endif()

# ====================================================================================================================================
# ------------------------------------------------------------ Packaging -------------------------------------------------------------
# ====================================================================================================================================

if(${MASTER_PROJECT})

    # Include standard isntall paths
    include(GNUInstallDirs)
    # Import helper functions for `ConfigVersion.cmak` file
    include(CMakePackageConfigHelpers)

    # Set path for CMake configuration files 
    set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

    # Generate `stm-utils-config.cmake` file
    configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/cmake/templates/${PROJECT_NAME}-config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
        INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
    )

    # Create a `ConfigVersion.cmake` file
    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )

    # Install the config and configversion files
    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
        DESTINATION ${INSTALL_CONFIGDIR}
    )

    # Register package in the User Package Registry
    export(PACKAGE ${PROJECT_NAME})

endif()

# ====================================================================================================================================
# ------------------------------------------------------- Helper configuration -------------------------------------------------------
# ====================================================================================================================================

# Prohibit builds in the source directory
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file)")
endif()
