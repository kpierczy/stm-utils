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

/* ========================================================== C mangling ========================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================= Declarations ========================================================= */

// Init value for the stack pointer. defined in linker script
extern unsigned long _estack;

// MCU's reset handler
void reser_handler(void) __attribute__((interrupt, noreturn));

/* ========================================================== Definitions ========================================================= */

// Shortcut macro for defining weakly aliased interrupt handler
#define ISR_VECTOR( handler_name ) void handler_name(void) __attribute__ ((interrupt, weak, alias("unused_vector")))

// Externally defined vector
#define ISR_VECTOR_EXTERN( handler_name ) extern void handler_name(void) __attribute__ ((interrupt))

// Shortcut macro for defining forced interrupt handler (for separate handlers of EXTIx lines)
#define ISR_VECTOR_FORCED( handler_name ) void handler_name(void) __attribute__ ((interrupt))

// Helper macro checking whether EXTI line's interrupt is pending
#define ExtiPends(flags, inp) ((flags) & (1<<(inp)))

/* ======================================================== Predefinitions ======================================================== */

// Unused vector handler
static __attribute__((interrupt)) void unused_vector(void) { while(1); };

/* ================================================================================================================================ */

#ifdef __cplusplus
}
#endif

/* ================================================================================================================================ */

#endif
