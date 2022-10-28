# ====================================================================================================================================
# @file       common.cmake
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 3rd August 2022 12:48:33 am
# @modified   Friday, 28th October 2022 9:40:36 pm
# @project    stm-utils
# @brief      Common part of toolchain files
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ====================================================================================================================================
# -------------------------------------------------------- Initial processing --------------------------------------------------------
# ====================================================================================================================================

# --------------------------------------------------------------------------------------------
# @brief In CMake only the first run of the toolchain file is guaranteed to see cached
#    variables (see [1]). As this files requires some variable(s) to be present every time,
#    the first run needs to store  their values in environmental variables
#
# @see [1] https://stackoverflow.com/questions/62795924/parameterizing-custom-cmake-toolchain
# --------------------------------------------------------------------------------------------

# Cache value of the OpenOCD target name
if(NOT DEFINED ENV{TOOLCHAIN_OPENOCD_DEFAULT_TARGET})

    # Include common definitions
    include(${CMAKE_CURRENT_LIST_DIR}/utilities/utilities.cmake)

    # Calculate default name for the OpenOCD target file
    remove_last_character(${DeviceFamily} TOOLCHAIN_OPENOCD_DEFAULT_TARGET)
    # Keep variable in env
    set(ENV{TOOLCHAIN_OPENOCD_DEFAULT_TARGET} ${TOOLCHAIN_OPENOCD_DEFAULT_TARGET})

endif()

# Cache CMAKE_BUILD_TYPE variable
if(NOT DEFINED ENV{TOOLCHAIN_CMAKE_BUILD_TYPE})
    set(ENV{TOOLCHAIN_CMAKE_BUILD_TYPE} ${CMAKE_BUILD_TYPE})
endif()

# Cache Core variable
if(NOT DEFINED ENV{Core})
    set(ENV{Core} ${Core})
endif()

# ====================================================================================================================================
# -------------------------------------------------------------- Options -------------------------------------------------------------
# ====================================================================================================================================

# Path to the linker scripts
set(LINKER_MEMORY_FILE "" CACHE FILEPATH "Path to the linker script defining memory layout"    )
set(LINKER_LAYOUT_FILE "" CACHE FILEPATH "Path to the linker script describing sections layout")
# Path to the toolchain root directory
set(TOOLCHAIN_ROOT "" CACHE PATH "Path to the root directory of the ARM Embedded Toolchain")

# Name of the OpenOCD debug interface file
set(TOOLCHAIN_OPENOCD_INTERFACE "stlink" CACHE STRING "Name of the OpenOCD debug interface file")
# Name of the OpenOCD target file
set(TOOLCHAIN_OPENOCD_TARGET "$ENV{TOOLCHAIN_OPENOCD_DEFAULT_TARGET}" CACHE STRING "Name of the OpenOCD debug interface file")

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
if(NOT ${TOOLCHAIN_ROOT} STREQUAL "")
    set(TOOLCHAIN_PATH_PREFIXED ${TOOLCHAIN_ROOT}/bin/arm-none-eabi-)
else()
    set(TOOLCHAIN_PATH_PREFIXED arm-none-eabi-)
endif()

# Toolchain tools (@note: g++ is used as linker executable to pass '-specs=' options to it at linkng phase)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PATH_PREFIXED}gcc${CMAKE_EXECUTABLE_SUFFIX}        CACHE INTERNAL "")
set(CMAKE_C_COMPILER   ${TOOLCHAIN_PATH_PREFIXED}gcc${CMAKE_EXECUTABLE_SUFFIX}        CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH_PREFIXED}g++${CMAKE_EXECUTABLE_SUFFIX}        CACHE INTERNAL "")
set(CMAKE_LINKER       ${TOOLCHAIN_PATH_PREFIXED}g++${CMAKE_EXECUTABLE_SUFFIX}        CACHE INTERNAL "")
set(CMAKE_AR           ${TOOLCHAIN_PATH_PREFIXED}gcc-ar${CMAKE_EXECUTABLE_SUFFIX}     CACHE INTERNAL "")
set(CMAKE_NM           ${TOOLCHAIN_PATH_PREFIXED}nm${CMAKE_EXECUTABLE_SUFFIX}         CACHE INTERNAL "")
set(CMAKE_OBJCOPY      ${TOOLCHAIN_PATH_PREFIXED}objcopy${CMAKE_EXECUTABLE_SUFFIX}    CACHE INTERNAL "")
set(CMAKE_OBJDUMP      ${TOOLCHAIN_PATH_PREFIXED}objdump${CMAKE_EXECUTABLE_SUFFIX}    CACHE INTERNAL "")
set(CMAKE_RANLIB       ${TOOLCHAIN_PATH_PREFIXED}gcc-ranlib${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_READELF      ${TOOLCHAIN_PATH_PREFIXED}readelf${CMAKE_EXECUTABLE_SUFFIX}    CACHE INTERNAL "")
set(CMAKE_SIZE	       ${TOOLCHAIN_PATH_PREFIXED}size${CMAKE_EXECUTABLE_SUFFIX}       CACHE INTERNAL "")
set(CMAKE_STRIP	       ${TOOLCHAIN_PATH_PREFIXED}strip${CMAKE_EXECUTABLE_SUFFIX}      CACHE INTERNAL "")
set(CMAKE_HEX          ${CMAKE_OBJCOPY} -O ihex                                       CACHE INTERNAL "")
set(CMAKE_BIN          ${CMAKE_OBJCOPY} -O binary -S                                  CACHE INTERNAL "")

# ====================================================================================================================================
# -------------------------------------------------------------- Flags ---------------------------------------------------------------
# ====================================================================================================================================

# Core flags
if(${Core} STREQUAL cortex-m0)
    set(CORE -mcpu=cortex-m0 -mfpu=auto -mfloat-abi=soft)
elseif(${Core} STREQUAL cortex-m0plus)
    set(CORE -mcpu=cortex-m0plus -mfpu=auto -mfloat-abi=soft)
elseif(${Core} STREQUAL cortex-m3)
    set(CORE -mcpu=cortex-m3 -mfpu=auto -mfloat-abi=soft)
elseif(${Core} STREQUAL cortex-m4)
    set(CORE -mcpu=cortex-m4 -mfpu=auto -mfloat-abi=soft)
elseif(${Core} STREQUAL cortex-m4f)
    set(CORE -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard)
elseif(${Core} STREQUAL cortex-m7f)
    set(CORE -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard)
elseif(${Core} STREQUAL cortex-m7dp)
    set(CORE -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard)
elseif(${Core} STREQUAL cortex-m33f)
    set(CORE -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard)
endif()
# Core (common) flags
set(CORE ${CORE} 
    -mthumb
)

# Debug flags
set(DEBUG 
    -gdwarf-2
    -DDEBUG
)

# Asm/C/C++ flags (@note: These flags performe 'garbage collection')
set(FLAGS
    -Wall
    -Wextra
    -fmessage-length=0
    -fsigned-char
    -fno-exceptions
    -fdata-sections
    -ffunction-sections
    -feliminate-unused-debug-types
    -MD
    -fno-math-errno
)

# Asm flags (Add '-x assembler-with-cpp' to preprocess C-directives not only in '.S' files but also in '.'s)
set(AS_SPECIFIC_FLAGS 
    -x assembler-with-cpp
)

# C/C++ flags
set(C_SPECIFIC_FLAGS "")

# C++ specific flags
set(CXX_SPECIFIC_FLAGS 
    -fabi-version=0
    -fno-exceptions
    -fno-rtti
    -fno-use-cxa-atexit
    -fno-threadsafe-statics
    -fconstexpr-depth=2048
)

# Linekr flags (@note: -specs= refers to GCC spec file that reside in ${toolchain}/arm-none-eabi/lib)
set(LD_SPECIFIC_FLAGS 
    --specs=nano.specs
    --specs=nosys.specs
    -Wl,--gc-sections
    # -u _printf_float
)

# ------------------------------------------------------ Build-specific flags --------------------------------------------------------

# Optimisation flags (debug)
set(DOPT
    -O0
    -ggdb
)

# Optimisation flags (release)
set(ROPT 
    -Os
    -flto
    -ffat-lto-objects
)

# C/CXX optimisation flags (release)
set(C_CXX_ROPT
    -fno-strict-aliasing
)

# Linker optimisation flags (release)
set(LD_ROPT
    -Wl,-flto
)

# -------------------------------------------------------- Flags Compilation ---------------------------------------------------------

# Compile compilation flags
set(ASM_FLAGS ${CORE} ${FLAGS}   ${AS_SPECIFIC_FLAGS}  CACHE INTERNAL "")
set(C_FLAGS   ${CORE} ${FLAGS}   ${C_SPECIFIC_FLAGS}   CACHE INTERNAL "")
set(CXX_FLAGS         ${C_FLAGS} ${CXX_SPECIFIC_FLAGS} CACHE INTERNAL "")
set(LD_FLAGS  ${CORE} ${FLAGS}   ${LD_SPECIFIC_FLAGS}  CACHE INTERNAL "")
# Build type flags
set(DEBUG_FLAGS   ${DOPT} ${DEBUG})
set(RELEASE_FLAGS ${ROPT}         )

# --------------------------------------------------------- Toolchain Flags ----------------------------------------------------------

# Debug-build flags
set(TOOLCHAIN_ASM_FLAGS_DEBUG      ${ASM_FLAGS}                                CACHE INTERNAL "asm debug compiler flags"  )
set(TOOLCHAIN_C_FLAGS_DEBUG        ${C_FLAGS}   ${DEBUG_FLAGS}                 CACHE INTERNAL "c debug compiler flags"    )
set(TOOLCHAIN_CXX_FLAGS_DEBUG      ${CXX_FLAGS} ${DEBUG_FLAGS}                 CACHE INTERNAL "cxx debug compiler flags"  )
set(TOOLCHAIN_LINKER_FLAGS_DEBUG   ${LD_FLAGS}  ${DEBUG_FLAGS}                 CACHE INTERNAL "debug linker flags"        )
# Release-build flags
set(TOOLCHAIN_ASM_FLAGS_RELEASE    ${ASM_FLAGS}                                CACHE INTERNAL "asm release compiler flags")
set(TOOLCHAIN_C_FLAGS_RELEASE      ${C_FLAGS}   ${RELEASE_FLAGS} ${C_CXX_ROPT} CACHE INTERNAL "c release compiler flags"  )
set(TOOLCHAIN_CXX_FLAGS_RELEASE    ${CXX_FLAGS} ${RELEASE_FLAGS} ${C_CXX_ROPT} CACHE INTERNAL "cxx release compiler flags")
set(TOOLCHAIN_LINKER_FLAGS_RELEASE ${LD_FLAGS}  ${RELEASE_FLAGS} ${LD_ROPT}    CACHE INTERNAL "release linker flags"      )

# ------------------------------------------------------ Compillation Options ----------------------------------------------------------

# Check if config is set
if(NOT ($ENV{TOOLCHAIN_CMAKE_BUILD_TYPE} STREQUAL "Debug") AND NOT ($ENV{TOOLCHAIN_CMAKE_BUILD_TYPE} STREQUAL "Release"))
    message(FATAL_ERROR "This toolchain file requires CMAKE_BUILD_TYPE to be set to either 'Debug' or 'Release' mode!")
endif()

# Compilation options for all targets
add_compile_options(
    "$<$<AND:$<CONFIG:RELEASE>,$<COMPILE_LANGUAGE:ASM>>:${TOOLCHAIN_ASM_FLAGS_RELEASE}>"
    "$<$<AND:$<CONFIG:DEBUG>,$<COMPILE_LANGUAGE:ASM>>:${TOOLCHAIN_ASM_FLAGS_DEBUG}>"
    "$<$<AND:$<CONFIG:RELEASE>,$<COMPILE_LANGUAGE:C>>:${TOOLCHAIN_C_FLAGS_RELEASE}>"
    "$<$<AND:$<CONFIG:DEBUG>,$<COMPILE_LANGUAGE:C>>:${TOOLCHAIN_C_FLAGS_DEBUG}>"
    "$<$<AND:$<CONFIG:RELEASE>,$<COMPILE_LANGUAGE:CXX>>:${TOOLCHAIN_CXX_FLAGS_RELEASE}>"
    "$<$<AND:$<CONFIG:DEBUG>,$<COMPILE_LANGUAGE:CXX>>:${TOOLCHAIN_CXX_FLAGS_DEBUG}>"
)

# Linkage options for all targets
add_link_options(
    "$<$<CONFIG:DEBUG>:${TOOLCHAIN_LINKER_FLAGS_DEBUG}>"
    "$<$<CONFIG:RELEASE>:${TOOLCHAIN_LINKER_FLAGS_RELEASE}>")
# Add memory layout script
if(NOT ${LINKER_MEMORY_FILE} STREQUAL "")
    add_link_options("SHELL:-T ${LINKER_MEMORY_FILE}")
endif()
# Add sections layout script
if(NOT ${LINKER_LAYOUT_FILE} STREQUAL "")
    add_link_options("SHELL:-T ${LINKER_LAYOUT_FILE}")
endif()

# ====================================================================================================================================
# --------------------------------------------------------------- Tools --------------------------------------------------------------
# ====================================================================================================================================

# OpenOCD flags
set(TOOLCHAIN_OPENOCD_FLAGS
    -finterface/${TOOLCHAIN_OPENOCD_INTERFACE}.cfg
    -ftarget/${TOOLCHAIN_OPENOCD_TARGET}.cfg
)

# ====================================================================================================================================
# ---------------------------------------------------- Crosscompilation Optimisation -------------------------------------------------
# ====================================================================================================================================

# (Optionally) Reduce compiler sanity check when cross-compiling
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# (Optionally) Sysroot settings
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
