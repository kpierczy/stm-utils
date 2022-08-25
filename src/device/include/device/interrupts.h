/* ============================================================================================================================= *//**
 * @file       interrupt.h
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 6th July 2021 2:08:23 pm
 * @modified   Tuesday, 6th July 2021 2:23:13 pm
 * @project    stm-utils
 * @brief      header file composing interrupt vectors' definitions for all STM32 microcontrollers
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * /// ============================================================================================================================ */

#ifndef __STM_UTILS_DEVICE__INTERUPT_H__
#define __STM_UTILS_DEVICE__INTERUPT_H__

/* =========================================================== Includes =========================================================== */

// Standard includes
#ifndef __cplusplus
#include <stdint.h>
#else
#include <cstdint>
#include <optional>
#endif
// ST includes
#include "device.h"

/* ========================================================= C++ inclusion ======================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================= Types ============================================================ */

/// Pointer to the ISR function
typedef void(*vector_function_ptr)(void);

/* ============================================================ Objects =========================================================== */

/// ISR vectors table
extern const vector_function_ptr isr_vectors_table[] __attribute__((section(".isr_vector")));

/* ================================================================================================================================ */

#ifdef __cplusplus
}
#endif

/* ================================================= Helper functions definitions ================================================= */

#ifndef __cplusplus

/**
 * @retval irqn 
 *    constant corresponding to the interrupt line of the NVIC controller
 *    used by the EXTIx line where x is given by @p index on success
 * @retval 0xFFFF'FFFF
 *    optional if @p idnex is out of range
 */
IRQn_Type get_exti_line_irqn(unsigned index);

#else
namespace device {

/**
 * @retval irqn 
 *    constant corresponding to the interrupt line of the NVIC controller
 *    used by the EXTIx line where x is given by @p index on success
 * @retval empty 
 *    optional if @p idnex is out of range
 */
std::optional<IRQn_Type> get_exti_line_irqn(unsigned index);

}
#endif

/* ================================================================================================================================ */

#endif
