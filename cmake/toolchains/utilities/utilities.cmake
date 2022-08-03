# ====================================================================================================================================
# @file       utilities.cmake
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 3rd August 2022 1:06:58 am
# @modified   Wednesday, 3rd August 2022 1:48:16 am
# @project    stm-utils
# @brief      Set of auxiliary CMake utilities
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# -----------------------------------------------------------------------------
# @brief Removes last character from @p str
# -----------------------------------------------------------------------------
function(remove_last_character input out_var)

    # Calculate size of the input
    string(LENGTH ${input} STR_LENGTH)
    # Decrement size
    math (EXPR STR_LENGTH "${STR_LENGTH} - 1" OUTPUT_FORMAT DECIMAL)
    # Get substring form the @p input
    string(SUBSTRING ${input} 0 ${STR_LENGTH} MODIFIED_STRING)

    # Set return value
    set(${out_var} ${MODIFIED_STRING} PARENT_SCOPE)

endfunction()
