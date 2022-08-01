/* ============================================================================================================================= *//**
 * @file       definitions.h
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 15th July 2021 10:16:05 am
 * @modified   Friday, 23rd July 2021 7:45:11 pm
 * @project    stm-utils
 * @brief      header file containing helper macros for ISR vectors' defining
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * /// ============================================================================================================================ */

#ifndef __STM_UTILS_DEVICE_INTERRUPTS_DEFINITIONS_H__
#define __STM_UTILS_DEVICE_INTERRUPTS_DEFINITIONS_H__

/* ========================================================= Declarations ========================================================= */

// Init value for the stack pointer. defined in linker script
extern unsigned long _estack;

// Pointer to the ISR function
typedef void(*vectFunctionPtr)(void);

// MCU's reset handler
void resetHandler(void) __attribute__((interrupt, noreturn));

/* ========================================================== Definitions ========================================================= */

// Shortcut macro for defining weakly aliased interrupt handler
#define ISR_VECTOR( handlerName ) void handlerName(void) __attribute__ ((interrupt, weak, alias("unusedVector")))

// Shortcut macro for defining forced interrupt handler (for separate handlers of EXTIx lines)
#define ISR_VECTOR_FORCED( handlerName ) void handlerName(void) __attribute__ ((interrupt))

// Helper macro checking whether EXTI line's interrupt is pending
#define ExtiPends(flags, inp) ((flags) & (1<<(inp)))

/* ================================================================================================================================ */

#endif
