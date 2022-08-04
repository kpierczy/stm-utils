/* ============================================================================================================================= *//**
 * @file       stm32g0xx.h
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 15th July 2021 10:14:58 am
 * @modified   Thursday, 15th July 2021 10:39:17 am
 * @project    stm-utils
 * @brief      Definitions of interrupt vectors for STMG0xx devices
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * /// ============================================================================================================================ */

#ifndef __STM_UTILS_DEVICE_INTERRUPTS_STMG0xx_H__
#define __STM_UTILS_DEVICE_INTERRUPTS_STMG0xx_H__

/* =========================================================== Includes =========================================================== */

#include "interrupts/definitions.h"

/* ========================================================== C mangling ========================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================== Definitions ========================================================= */

/**
 * @note Names for SVC_Handler, PendSV_Handler and SysTick_Handler interrupt
 *    handlers was set differently to fit RTX-RTOSv5 naming scheme
 */

// Exception vector's definitions
ISR_VECTOR       (EXC_NMI);
ISR_VECTOR       (EXC_HardFault);
ISR_VECTOR       (EXC_MemoryManagement);
ISR_VECTOR       (SVC_Handler);
ISR_VECTOR       (PendSV_Handler);
ISR_VECTOR       (SysTick_Handler);

// ISR Vector's definitions
ISR_VECTOR       (ISR_WWDG);
ISR_VECTOR       (ISR_RTC_TAMP);
ISR_VECTOR       (ISR_FLASH);
ISR_VECTOR       (ISR_RCC);
ISR_VECTOR_FORCED(ISR_EXTI0_1);
ISR_VECTOR_FORCED(ISR_EXTI2_3);
ISR_VECTOR_FORCED(ISR_EXTI4_15);
ISR_VECTOR       (ISR_DMA1_Channel1);
ISR_VECTOR       (ISR_DMA1_Channel2_3);
ISR_VECTOR       (ISR_DMA1_Ch4_5_DMAMUX1_OVR);
ISR_VECTOR       (ISR_ADC1);
ISR_VECTOR       (ISR_TIM1_BRK_UP_TRG_COM);
ISR_VECTOR       (ISR_TIM1_CC);
ISR_VECTOR       (ISR_TIM3);
ISR_VECTOR       (ISR_TIM14);
ISR_VECTOR       (ISR_TIM16);
ISR_VECTOR       (ISR_TIM17);
ISR_VECTOR       (ISR_I2C1);
ISR_VECTOR       (ISR_I2C2);
ISR_VECTOR       (ISR_SPI1);
ISR_VECTOR       (ISR_SPI2);
ISR_VECTOR       (ISR_USART1);
ISR_VECTOR       (ISR_USART2);

/* ========================================================= Pseud-vectors ======================================================== */

// Pseudo-ISR vectors
ISR_VECTOR       (ISR_EXTI1);
ISR_VECTOR       (ISR_EXTI2);
ISR_VECTOR       (ISR_EXTI3);
ISR_VECTOR       (ISR_EXTI4);
ISR_VECTOR       (ISR_EXTI5);
ISR_VECTOR       (ISR_EXTI6);
ISR_VECTOR       (ISR_EXTI7);
ISR_VECTOR       (ISR_EXTI8);
ISR_VECTOR       (ISR_EXTI9);
ISR_VECTOR       (ISR_EXTI10);
ISR_VECTOR       (ISR_EXTI11);
ISR_VECTOR       (ISR_EXTI12);
ISR_VECTOR       (ISR_EXTI13);
ISR_VECTOR       (ISR_EXTI14);
ISR_VECTOR       (ISR_EXTI15);

/* ================================================================================================================================ */

#ifdef __cplusplus
}
#endif

/* ================================================================================================================================ */

#endif
