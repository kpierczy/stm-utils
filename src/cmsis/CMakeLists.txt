# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 14th June 2021 6:53:51 pm
# @modified   Monday, 1st August 2022 10:32:51 pm
# @project    stm-utils
# @brief      Aggregating library gathering all CMSIS submodules
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Add CMSIS::Core library
add_subdirectory(core)
# Add CMSIS::RTOS library
add_subdirectory(rtos)

# Define library
add_library(cmsis INTERFACE)

# Link dependancies
target_link_libraries(cmsis
    INTERFACE
        stm-utils::cmsis::core
        stm-utils::cmsis::rtos
)

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