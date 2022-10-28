# ====================================================================================================================================
# @file       helpers.cmake
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 14th July 2021 11:45:35 am
# @modified   Friday, 28th October 2022 9:44:00 pm
# @project    stm-utils
# @brief      Helper function for CMake scripts
#    
# @copyright Krzysztof Pierczyk © 2021
# ====================================================================================================================================

# ====================================================================================================================================
# ----------------------------------------------------- General helper functions -----------------------------------------------------
# ====================================================================================================================================

# Adds linker option to a target that generates memory map file
function(add_memory_map_generation exec_target map_path)
    target_link_options(${exec_target} PRIVATE -Wl,-Map=${map_path})
endfunction()


# Adds command to the target that generates size log of the binary file after build
function(add_size_log_command target)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_SIZE} --format=berkeley $<TARGET_FILE:${target}>)
endfunction()


# Adds command to the target that generates log file of symbols
function(add_symbols_log_command target log_path)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_NM} --print-size --size-sort --radix=d $<TARGET_FILE:${target}> > ${log_path})
endfunction()


# Adds command to the target that generates readelf log
function(add_readelf_log_command target log_path)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_READELF} -all $<TARGET_FILE:${target}> > ${log_path})
endfunction()


# Aggregating function for overlying targets
function(add_executable_logs target)

    # Custom linker script & memory map generation
    generateMemoryMap(${target} ${CMAKE_CURRENT_BINARY_DIR}/${target}_map)
    # Binary file sizing
    generateSizeLog(${target})
    # Symbols' listing
    generateSymbolLog(${target} ${CMAKE_CURRENT_BINARY_DIR}/${target}_symlog)
    # Readelf
    generateReadelfLog(${target} ${CMAKE_CURRENT_BINARY_DIR}/${target}_readelf)
    
endfunction()


# Additional global target removing all project's installs
add_custom_target(clean_installs
    COMMAND COMMAND ${CMAKE_COMMAND} -E rm -rf 
        ${CMAKE_SOURCE_DIR}/bin
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/include
)


# Additional global target removing all project's outputs
add_custom_target(clean_project
    COMMAND COMMAND ${CMAKE_COMMAND} -E rm -rf 
        ${CMAKE_SOURCE_DIR}/build
    DEPENDS 
        clean_installs
)

# ====================================================================================================================================
# --------------------------------------------------- Executable generation helper ---------------------------------------------------
# ====================================================================================================================================

# -----------------------------------------------------------------------------
# @brief Produces .hex and .bin files from ELF target
#
# @param target
#    name of the ELF target
# @param HEX_NAME
#    name of the resulting .hex file
# @param target
#    name of the resulting .bin file
# -----------------------------------------------------------------------------
function(generate_bin_hex_from_target target)
    
    # -------------------------- Parse arguments -------------------------

    # Options arguments
    set(OPTIONS_ARGUMENTS
        LIST_SECTIONS
    )

    # Single-value arguments
    set(SINGLE_ARGUMENTS
        HEX_NAME
        BIN_NAME
    )

    # Set arg prefix
    set(ARG_PREFIX "ARG")
    # Parse arguments
    cmake_parse_arguments(${ARG_PREFIX}
        "${OPTIONS_ARGUMENTS}"
        "${SINGLE_ARGUMENTS}"
        ""
        ${ARGN}
    )

    # --------------------------------------------------------------------

    # Prepare binaries-summary commands
    set(SUMMARY_CMD 
            ${CMAKE_COMMAND} -E echo "--- Binaries summary:"
        COMMAND
            ${CMAKE_SIZE} --format=berkeley $<TARGET_FILE:${target}>)
    # Prepare binaries-summary commands
    if(ARG_LIST_SECTIONS)
    set(SUMMARY_CMD ${SUMMARY_CMD}
        COMMAND 
            ${CMAKE_COMMAND} -E echo "--- Sections summary:"
        COMMAND
            ${CMAKE_SIZE} --format=sysv $<TARGET_FILE:${target}>)
    endif()

    # Generate .hex and .bin binaries
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex   $<TARGET_FILE:${target}> ${CMAKE_BINARY_DIR}/${ARG_HEX_NAME}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${target}> ${CMAKE_BINARY_DIR}/${ARG_BIN_NAME}
        COMMAND ${SUMMARY_CMD}
        COMMENT "Building ${ARG_HEX_NAME}
                Building ${ARG_BIN_NAME}"
    )

endfunction()

# ====================================================================================================================================
# --------------------------------------------------- MCU-related helper functions ---------------------------------------------------
# ====================================================================================================================================

# Adds flashing target to the executable target
function(add_flash_target target)
    add_custom_target(flash_${target}
        COMMAND ${OPENOCD_PATH} ${TOOLCHAIN_OPENOCD_FLAGS} -c 'program $<TARGET_FILE:${target}> verify reset exit'
        DEPENDS ${target})
endfunction()


# Additional global target erasing MCU's memory
function(add_erase_memory_target target)
    add_custom_target(target
        COMMAND ${OPENOCD_PATH} ${TOOLCHAIN_OPENOCD_FLAGS} -c 'init; reset halt; stm32f4x mass_erase 0; exit'
    )
endfunction()
