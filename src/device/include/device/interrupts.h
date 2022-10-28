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
inline IRQn_Type get_exti_line_irqn(unsigned index);

#else

namespace device {

/**
 * @retval irqn 
 *    constant corresponding to the interrupt line of the NVIC controller
 *    used by the EXTIx line where x is given by @p index on success
 * @retval empty 
 *    optional if @p idnex is out of range
 */
template<unsigned index>
inline std::optional<IRQn_Type> get_exti_line_irqn();

}

#endif

/* ==================================================== Implementation includes =================================================== */

// Include device-specific headers
#if defined(STM32MCU_MAJOR_TYPE_F0)
#include "device/interrupts/stm32f0xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_F1)
#include "device/interrupts/stm32f1xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_F2)
#include "device/interrupts/stm32f2xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_F3)
#include "device/interrupts/stm32f3xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_F4)
#include "device/interrupts/stm32f4xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_F7)
#include "device/interrupts/stm32f7xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_G0)
#include "device/interrupts/stm32g0xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_G4)
#include "device/interrupts/stm32g4xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_H7)
#include "device/interrupts/stm32h7xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_L0)
#include "device/interrupts/stm32l0xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_L1)
#include "device/interrupts/stm32l1xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_L4)
#include "device/interrupts/stm32l4xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_L5)
#include "device/interrupts/stm32l5xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_WL)
#include "device/interrupts/stm32wlxx.h"
#elif defined(STM32MCU_MAJOR_TYPE_WB)
#include "device/interrupts/stm32wbxx.h"
#else
#error Unknown MCU major type
#endif

/* ================================================================================================================================ */

#endif
