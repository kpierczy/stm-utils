# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 14th June 2021 6:53:51 pm
# @modified   Tuesday, 23rd August 2022 1:56:33 pm
# @project    stm-utils
# @brief      Aggregating library gathering all CMSIS submodules
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ====================================================================================================================================
# ------------------------------------------------------------ Options ---------------------------------------------------------------
# ====================================================================================================================================

# Flag deciding whether to add RTX RTOS target to the build
set(USE_CMSIS_RTOS ON CACHE BOOL "If TRUE the library will add RTX RTOS to CMake targets")
   
# ====================================================================================================================================
# ----------------------------------------------------------- Components -------------------------------------------------------------
# ====================================================================================================================================
 
# Add CMSIS::Core library
add_subdirectory(core)
# Add CMSIS::RTOS library
if(USE_CMSIS_RTOS)
    add_subdirectory(rtos)
endif()

# Define library
add_library(cmsis INTERFACE)

# Link CMSIS base
target_link_libraries(cmsis
    INTERFACE
        stm-utils::cmsis::core)
# Link RTX RTOS
if(USE_CMSIS_RTOS)
    target_link_libraries(cmsis
        INTERFACE
            stm-utils::cmsis::rtos)
endif()

# Alias for the library
add_library(stm-utils::cmsis ALIAS cmsis)

# ====================================================================================================================================
# ------------------------------------------------------ Targets' installation -------------------------------------------------------
# ====================================================================================================================================

if(${MASTER_PROJECT})

    # Include standard isntall paths
    include(GNUInstallDirs)

    # Install cmsis target
    install(TARGETS cmsis
        EXPORT
            stm-utils-targets
        LIBRARY
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

    # Set exported name of the `cmsis` target to `CMSIS`
    set_target_properties(cmsis PROPERTIES EXPORT_NAME CMSIS)

endif()