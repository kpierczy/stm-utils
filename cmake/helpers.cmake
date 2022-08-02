# ====================================================================================================================================
# @file       helpers.cmake
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 14th July 2021 11:45:35 am
# @modified   Wednesday, 3rd August 2022 1:18:39 am
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
