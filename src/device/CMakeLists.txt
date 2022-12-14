# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 14th June 2021 6:53:51 pm
# @modified   Friday, 28th October 2022 8:24:36 pm
# @project    stm-utils
# @brief      Device-specifix CMSIS interface implementation
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ====================================================================================================================================
# -------------------------------------------------------- Library fedinition --------------------------------------------------------
# ====================================================================================================================================

# Define library
add_library(device
    src/device/system_${DeviceFamily}.c
    src/interrupts/vectors/${DeviceFamily}.c
    src/interrupts/${DeviceFamily}.cpp
    src/startup.c
)

# Add ST-secific defines
target_compile_definitions(device
    PUBLIC
        ${DEVICE}
        ${DeviceType}
)
# Add ST-secific defines (dual-core devices only)
if(DEFINED TargetCore)
    target_compile_definitions(device
        PUBLIC
            ${TargetCore}
    )
endif()

# Add HAL build information
if(HAL_BUILD)
    target_compile_definitions(device
        PUBLIC
            USE_HAL_DRIVER
    )
endif()

# Add header files
target_include_directories(device
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/device/st>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/device/st/${DeviceFamily}>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/interrupts/include>
)

# Link dependancies
target_link_libraries(device
    stm-utils::hal
    stm-utils::cmsis::core
)

# Alias for the library
add_library(stm-utils::device ALIAS device)

# ====================================================================================================================================
# ------------------------------------------------------- Build configruation --------------------------------------------------------
# ====================================================================================================================================

# Silence some library warnings
target_compile_options(device
    PUBLIC
        -Wno-unused-parameter
        -Wno-unused-function
)

target_compile_options(device
    PUBLIC
        -D${DEVICE}
)

# ====================================================================================================================================
# ------------------------------------------------------ Targets' installation -------------------------------------------------------
# ====================================================================================================================================

if(${MASTER_PROJECT})

    # Include standard isntall paths
    include(GNUInstallDirs)

    # Install device target
    install(
        TARGETS
            device
        EXPORT
            stm-utils-targets
        LIBRARY
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

    # Set exported name of the `device` target to `Device`
    set_target_properties(device PROPERTIES EXPORT_NAME Device)

    # Install header files
    install(DIRECTORY include/                             DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.h" )
    install(FILES     include/device/${DeviceFamily}.h     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}                              )
    install(DIRECTORY include/device/${DeviceFamily}/      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}                              )
    install(FILES     include/interrupts/definitions.h     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/interrupts                   )
    install(FILES     include/interrupts/${DeviceFamily}.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/interrupts                   )
    install(DIRECTORY scripts/                             DESTINATION ${CMAKE_INSTALL_PREFIX}/config                           )

endif()
