# ====================================================================================================================================
# @file       CMakeLists.txt
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Monday, 14th June 2021 6:53:51 pm
# @modified   Friday, 28th October 2022 9:37:41 pm
# @project    stm-utils
# @brief      CMSIS package for an arbitrary Cortex-M platform
#
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ====================================================================================================================================
# ------------------------------------------------------------- Options --------------------------------------------------------------
# ====================================================================================================================================

# Path to the include directory containing RTX_Components.h and RTX_Config.h files
set(RTX_CONFIG_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/config" CACHE PATH    
    "Path to the include directory containing RTX_Components.h and RTX_Config.h files")
# Path to the RTX_Config.c config file
set(RTX_CONFIG_FILE "${CMAKE_CURRENT_LIST_DIR}/config/RTX_Config.c" CACHE FILEPATH
    "Path to the RTX_Config.c config file")
# Path to the RTX_Handlers.c config file
set(RTX_HANDLERS_FILE "${CMAKE_CURRENT_LIST_DIR}/config/RTX_Handlers.c" CACHE FILEPATH
    "Path to the RTX_Handlers.c config file")

# ====================================================================================================================================
# ------------------------------------------------------------- Library --------------------------------------------------------------
# ====================================================================================================================================

# Select architecture
if(${Core} STREQUAL cortex-m0)
    set(Architecture armv6m)
elseif(${Core} STREQUAL cortex-m0plus)
    set(Architecture armv6m)
elseif(${Core} STREQUAL cortex-m3)
    set(Architecture armv7m)
elseif(${Core} STREQUAL cortex-m4)
    set(Architecture armv7m)
elseif(${Core} STREQUAL cortex-m4f)
    set(Architecture armv7m)
elseif(${Core} STREQUAL cortex-m7f)
    set(Architecture armv7m)
elseif(${Core} STREQUAL cortex-m7dp)
    set(Architecture armv7m)
elseif(${Core} STREQUAL cortex-m33f)
    set(Architecture armv8mbl)
endif()

# Define library
add_library(cmsis_rtos
    ${RTX_CONFIG_FILE}
    ${RTX_HANDLERS_FILE}
    src/os_systick.c
    src/rtx/src/rtx_delay.c
    src/rtx/src/rtx_evr.c
    src/rtx/src/rtx_lib.c
    src/rtx/src/rtx_memory.c
    src/rtx/src/rtx_msgqueue.c
    src/rtx/src/rtx_semaphore.c
    src/rtx/src/rtx_thread.c
    src/rtx/src/rtx_evflags.c
    src/rtx/src/rtx_kernel.c
    src/rtx/src/rtx_mempool.c
    src/rtx/src/rtx_mutex.c
    src/rtx/src/rtx_system.c
    src/rtx/src/rtx_timer.c
    src/rtx/src/gcc/irq_${Architecture}.S
)

# Include cmsis directory
target_include_directories(cmsis_rtos 
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${RTX_CONFIG_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/rtx/include
)

# Alias for the library
add_library(stm-utils::cmsis::rtos ALIAS cmsis_rtos)

# ====================================================================================================================================
# ------------------------------------------------------- Compilation settings -------------------------------------------------------
# ====================================================================================================================================

# RTX-specific constants
target_compile_definitions(cmsis_rtos
    PRIVATE 
        # Additional flag including RTE header files to sources
        _RTE_
        # CMSIS Device include file of the target
        CMSIS_device_header="${DeviceFamily}.h"
)

# Target dependancies
target_link_libraries(cmsis_rtos
    stm-utils::device
    stm-utils::cmsis::core
)

# ====================================================================================================================================
# --------------------------------------------------------- Installations ------------------------------------------------------------
# ====================================================================================================================================

if(${MASTER_PROJECT})

    # Include standard isntall paths
    include(GNUInstallDirs)

    # Install cmsis_rtos target
    install(TARGETS cmsis_rtos
        EXPORT
            stm-utils-targets
        LIBRARY
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

    # Set exported name of the `cmsis_rtos` target to `cmsis::rtos`
    set_target_properties(cmsis_rtos PROPERTIES EXPORT_NAME cmsis::rtos)

    # Install header files
    install(DIRECTORY include/                   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install(DIRECTORY ${RTX_CONFIG_INCLUDE_DIR}/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

endif()
