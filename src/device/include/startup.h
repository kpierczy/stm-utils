/* ============================================================================================================================= *//**
 * @file       startup.h
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 6th July 2021 1:36:47 pm
 * @modified   Thursday, 15th July 2021 11:11:28 am
 * @project    stm-utils
 * @brief      Functions related to the MCU's startup
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * /// ============================================================================================================================ */

#ifndef __STM_UTILS_STARTUP_H__
#define __STM_UTILS_STARTUP_H__

/* ========================================================== C mangling ========================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================= Declarations ========================================================= */

/**
 * @brief Empty stub function
 */
void stub_function();

/**
 * @brief Function called just after initialization of the MCU
 */
void startup_extension(void) __attribute__ ((weak));

/**
 * @brief Function called just after deinitialization of the MCU
 */
void exit_extension(void) __attribute__ ((weak));

/* ================================================================================================================================ */

#ifdef __cplusplus
}
#endif

/* ================================================================================================================================ */

#endif
