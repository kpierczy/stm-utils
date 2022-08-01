# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 14th June 2021 6:53:51 pm
# @modified   Monday, 1st August 2022 10:33:37 pm
# @project    stm-utils
# @brief      CMake file for CMSIS::Core target holding definitions of the standard CMSIS Core interface
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Define library
add_library(cmsis_core INTERFACE)

# Include config directory
target_include_directories(cmsis_core 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Alias for the library
add_library(stm-utils::cmsis::core ALIAS cmsis_core)

# ====================================================================================================================================
# --------------------------------------------------------- Installations ------------------------------------------------------------
# ====================================================================================================================================

if(${MASTER_PROJECT})

    # Include standard isntall paths
    include(GNUInstallDirs)

    # Install cmsis_core target
    install(TARGETS cmsis_core
        EXPORT
            stm-utils-targets
    )

    # Set exported name of the `cmsis_core` target to `CMSIS::Core`
    set_target_properties(cmsis_core PROPERTIES EXPORT_NAME CMSIS::Core)

    # Install header files
    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

endif()
