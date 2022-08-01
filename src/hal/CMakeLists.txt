# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 14th June 2021 6:53:50 pm
# @modified   Monday, 1st August 2022 10:32:06 pm
# @project    stm-utils
# @brief      CMakeList for used elements of HAL library
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ====================================================================================================================================
# ------------------------------------------------------------ Options ---------------------------------------------------------------
# ====================================================================================================================================

# Target device
option(USE_FULL_LL "If true, full LL library is built" ON)
# Target device
option(HAL_BUILD "If true, HAL library is built on top of LL" ON)

# ====================================================================================================================================
# ------------------------------------------------------- Library definition ---------------------------------------------------------
# ====================================================================================================================================

# Get LL sources for specific device
file(GLOB LlSources  ${CMAKE_CURRENT_SOURCE_DIR}/src/ll/${DeviceFamily}/*.c)
# Get HAL sources for specific device
if(HAL_BUILD)
    file(GLOB HalSources ${CMAKE_CURRENT_SOURCE_DIR}/src/hal/${DeviceFamily}/*.c)
endif()
# Get legacy HAL sources if exist
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/hal/${DeviceFamily}/Legacy)
    file(GLOB HalLegacySources ${CMAKE_CURRENT_SOURCE_DIR}/src/hal/${DeviceFamily}/Legacy/*.c)
endif()

# Add a library
add_library(hal
    ${HalSources}
    ${HalLegacySources}
    ${LlSources}
)

# Add compilation flags
if(${USE_FULL_LL})
    target_compile_options(hal
        PUBLIC
            "-DUSE_FULL_LL_DRIVER"
    )
endif()

# Include include directories
target_include_directories(hal
    PUBLIC 
        $<INSTALL_INTERFACE:include>       
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/config>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/config/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/ll/${DeviceFamily}>
)

# Add HAL includes if build requested
if(HAL_BUILD)
    target_include_directories(hal PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/hal/${DeviceFamily}>)
endif()

# Add legacy include directory, if exist
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include/hal/${DeviceFamily}/Legacy)
    target_include_directories(hal PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/hal/${DeviceFamily}/Legacy>)
endif()

# Link dependancies
target_link_libraries(hal
    ${PROJECT_NAME}::device
    ${PROJECT_NAME}::cmsis::core
)

# Alias for the library
add_library(${PROJECT_NAME}::hal ALIAS hal)

# ====================================================================================================================================
# ------------------------------------------------------- Build configruation --------------------------------------------------------
# ====================================================================================================================================

# Silence some library warnings
target_compile_options(hal
    -Wno-unused-parameter
    -Wno-unused-but-set-variable
    -Wno-unused-function
)

# Additional definitions
target_compile_definitions(hal
    PUBLIC
        ${DeviceType}
)

# ====================================================================================================================================
# --------------------------------------------------------- Installations ------------------------------------------------------------
# ====================================================================================================================================

if(${MASTER_PROJECT})

    # Include standard isntall paths
    include(GNUInstallDirs)

    # Install hal target
    install(TARGETS hal
        EXPORT
            ${PROJECT_NAME}-targets
        LIBRARY
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

    # Set exported name of the `hal` target to `HAL`
    set_target_properties(hal PROPERTIES EXPORT_NAME HAL)

    # Install include header files
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/config/                             DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/config/include/                     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install(FILES     ${CMAKE_CURRENT_SOURCE_DIR}/include/stm32_hal.h                 DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/hal/${DeviceFamily}/        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/hal/${DeviceFamily}/Legacy/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ll/                         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.h")
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ll/${DeviceFamily}/         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    # Install legacy include LL directory, if exist
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include/ll/${DeviceFamily}/Legacy)
        install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ll/${DeviceFamily}/Legacy/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    endif()

    # Install legacy include HAL directory, if exist
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include/hal/${DeviceFamily}/Legacy)
        install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/hal/${DeviceFamily}/Legacy/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    endif()

endif()
