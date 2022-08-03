# ====================================================================================================================================
# @file       common.cmake
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 3rd August 2022 12:48:33 am
# @modified   Wednesday, 3rd August 2022 1:54:52 am
# @project    stm-utils
# @brief      Common part of toolchain files
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Include device analysis
include(${CMAKE_CURRENT_LIST_DIR}/../device.cmake)
# Include common definitions
include(${CMAKE_CURRENT_LIST_DIR}/utilities/utilities.cmake)

# Calculate default name for the OpenOCD target file
remove_last_character(${DeviceFamily} TOOLCHAIN_OPENOCD_DEFAULT_TARGET)

# ====================================================================================================================================
# -------------------------------------------------------------- Options -------------------------------------------------------------
# ====================================================================================================================================

# Path to the linker scripts
set(LINKER_LAYOUT_FILE ${CMAKE_SOURCE_DIR}/tools/gcc-arm-none-eabi    CACHE FILEPATH "Path to the linker script describing sections layout")
set(LINKER_MEMORY_FILE ${CMAKE_SOURCE_DIR}/src/device/scripts/link.ld CACHE FILEPATH "Path to the linker script defining memory layout"    )
# Path to the toolchain root directory
set(TOOLCHAIN_ROOT ${CMAKE_SOURCE_DIR}/tools/gcc-arm-none-eabi CACHE PATH "Path to the root directory of the ARM Embedded Toolchain")

# Name of the OpenOCD debug interface file
set(TOOLCHAIN_OPENOCD_INTERFACE "stlink" CACHE STRING "Name of the OpenOCD debug interface file")
# Name of the OpenOCD target file
set(TOOLCHAIN_OPENOCD_TARGET "${TOOLCHAIN_OPENOCD_DEFAULT_TARGET}" CACHE STRING "Name of the OpenOCD debug interface file")

# ====================================================================================================================================
# ------------------------------------------------------------ Definitions -----------------------------------------------------------
# ====================================================================================================================================

# Toolchain platform
set(CMAKE_SYSTEM_NAME Generic)
# Toolchain target CPU
set(CMAKE_SYSTEM_PROCESSOR arm)

# ====================================================================================================================================
# ------------------------------------------------------------- Toolchain ------------------------------------------------------------
# ====================================================================================================================================

# Toolchain path with prefix
set(TOOLCHAIN_PATH_PREFIXED ${TOOLCHAIN_ROOT}/bin/arm-none-eabi)

# Toolchain tools (@note: g++ is used as linker executable to pass '-specs=' options to it at linkng phase)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PATH_PREFIXED}-gcc${CMAKE_EXECUTABLE_SUFFIX}        CACHE INTERNAL "")
set(CMAKE_C_COMPILER   ${TOOLCHAIN_PATH_PREFIXED}-gcc${CMAKE_EXECUTABLE_SUFFIX}        CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH_PREFIXED}-g++${CMAKE_EXECUTABLE_SUFFIX}        CACHE INTERNAL "")
set(CMAKE_LINKER       ${TOOLCHAIN_PATH_PREFIXED}-g++${CMAKE_EXECUTABLE_SUFFIX}        CACHE INTERNAL "")
set(CMAKE_AR           ${TOOLCHAIN_PATH_PREFIXED}-gcc-ar${CMAKE_EXECUTABLE_SUFFIX}     CACHE INTERNAL "")
set(CMAKE_NM           ${TOOLCHAIN_PATH_PREFIXED}-nm${CMAKE_EXECUTABLE_SUFFIX}         CACHE INTERNAL "")
set(CMAKE_OBJCOPY      ${TOOLCHAIN_PATH_PREFIXED}-objcopy${CMAKE_EXECUTABLE_SUFFIX}    CACHE INTERNAL "")
set(CMAKE_OBJDUMP      ${TOOLCHAIN_PATH_PREFIXED}-objdump${CMAKE_EXECUTABLE_SUFFIX}    CACHE INTERNAL "")
set(CMAKE_RANLIB       ${TOOLCHAIN_PATH_PREFIXED}-gcc-ranlib${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_READELF      ${TOOLCHAIN_PATH_PREFIXED}-readelf${CMAKE_EXECUTABLE_SUFFIX}    CACHE INTERNAL "")
set(CMAKE_SIZE	       ${TOOLCHAIN_PATH_PREFIXED}-size${CMAKE_EXECUTABLE_SUFFIX}       CACHE INTERNAL "")
set(CMAKE_STRIP	       ${TOOLCHAIN_PATH_PREFIXED}-strip${CMAKE_EXECUTABLE_SUFFIX}      CACHE INTERNAL "")
set(CMAKE_HEX          ${CMAKE_OBJCOPY} -O ihex                                        CACHE INTERNAL "")
set(CMAKE_BIN          ${CMAKE_OBJCOPY} -O binary -S                                   CACHE INTERNAL "")
