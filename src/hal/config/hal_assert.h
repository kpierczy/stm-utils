/* ============================================================================================================================= *//**
 * @file       hal_assert.h
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Friday, 16th July 2021 9:40:38 am
 * @modified   Friday, 16th July 2021 3:35:49 pm
 * @project    stm-utils
 * @brief      Declaration of an assert function and macro used by the HAL drivers
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * /// ============================================================================================================================ */

#ifndef __STM_UTILS_HAL_ASSERT_H__
#define __STM_UTILS_HAL_ASSERT_H__

/* ========================================================== C mangling ========================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================= Declarations ========================================================= */

// If full assert is used along HAL library
#ifdef  USE_FULL_ASSERT

/**
 * @brief Reports assert's failure during processing HAL function
 * @param file 
 *    source file that the assertion failed in
 * @param line 
 *    source file's line that the assertion failed at
 */
void assert_failed(uint8_t* file, uint32_t line);


/**
 * @brief  The assert_param macro is used for function's parameters check.
 * @param  expr If expr is false, it calls assert_failed function
 *         which reports the name of the source file and the source
 *         line number of the call that failed.
 */
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))

// If no assert is used along HAL library
#else

/**
 * @brief  The assert_param macro is used for function's parameters check.
 * @param  expr If expr is false, it calls assert_failed function
 *         which reports the name of the source file and the source
 *         line number of the call that failed.
 */
#define assert_param(expr) ((void) 0U)

#endif

/* ================================================================================================================================ */

#ifdef __cplusplus
}
#endif

/* ================================================================================================================================ */

#endif
