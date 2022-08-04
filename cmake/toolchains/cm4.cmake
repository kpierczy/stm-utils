# ====================================================================================================================================
# @file       cm4.cmake
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Tuesday, 22nd June 2021 6:14:51 pm
# @modified   Thursday, 4th August 2022 1:32:14 am
# @project    stm-utils
# @brief      CMake toolchain for ARM Cortex-M4
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# Include common definitions
include(${CMAKE_CURRENT_LIST_DIR}/common.cmake)

# ====================================================================================================================================
# -------------------------------------------------------------- Flags ---------------------------------------------------------------
# ====================================================================================================================================

# Core flags
set(CORE
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -mthumb
)

# Debug flags
set(DEBUG 
    -gdwarf-2
    -DDEBUG
)

# Optimisation level (release and debug)
set(DOPT -O2 -ggdb)
set(ROPT -O2      )

# Asm/C/C++ flags (@note: These flags performe 'garbage collection')
set(FLAGS
    -Wall
    -Wextra
    -fno-exceptions
    -fdata-sections
    -ffunction-sections
    -feliminate-unused-debug-types
)

# Asm flags (Add '-x assembler-with-cpp' to preprocess C-directives not only in '.S' files but also in '.'s)
set(AS_SPECIFIC_FLAGS "")

# C/C++ flags
set(C_SPECIFIC_FLAGS "")

# C++ specific flags
set(CXX_SPECIFIC_FLAGS 
    -fconcepts-diagnostics-depth=4
)

# Linekr flags (@note: -specs= refers to GCC spec file that reside in ${toolchain}/arm-none-eabi/lib)
set(LD_SPECIFIC_FLAGS 
    --specs=nano.specs
    --specs=nosys.specs
    -Wl,--gc-sections
    # -u _printf_float
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
set(TOOLCHAIN_ASM_FLAGS_DEBUG    ${ASM_FLAGS}  CACHE INTERNAL               "")
set(TOOLCHAIN_C_FLAGS_DEBUG      ${C_FLAGS}   ${DEBUG_FLAGS} CACHE INTERNAL "")
set(TOOLCHAIN_CXX_FLAGS_DEBUG    ${CXX_FLAGS} ${DEBUG_FLAGS} CACHE INTERNAL "")
set(TOOLCHAIN_LINKER_FLAGS_DEBUG ${LD_FLAGS}  ${DEBUG_FLAGS} CACHE INTERNAL "")
# Release-build flags
set(TOOLCHAIN_ASM_FLAGS_RELEASE    ${ASM_FLAGS} ${RELEASE_FLAGS} CACHE INTERNAL "")
set(TOOLCHAIN_C_FLAGS_RELEASE      ${C_FLAGS}   ${RELEASE_FLAGS} CACHE INTERNAL "")
set(TOOLCHAIN_CXX_FLAGS_RELEASE    ${CXX_FLAGS} ${RELEASE_FLAGS} CACHE INTERNAL "")
set(TOOLCHAIN_LINKER_FLAGS_RELEASE ${LD_FLAGS}  ${RELEASE_FLAGS} CACHE INTERNAL "")

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
    # -save-temps=obj
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
add_link_options("SHELL:-T ${LINKER_LAYOUT_FILE}")

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
