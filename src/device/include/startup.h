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

/* ========================================================= Declarations ========================================================= */

/**
 * @brief Empty stub function
 */
void stubFunction();

/**
 * @brief Function called just after initialization of the MCU
 */
void startupExtension(void) __attribute__ ((weak));

/**
 * @brief Function called just after deinitialization of the MCU
 */
void exitExtension(void) __attribute__ ((weak));

/* ================================================================================================================================ */

#endif
