/* ============================================================================================================================= *//**
 * @file       stm32f4xx.h
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 15th July 2021 10:14:58 am
 * @modified   Friday, 23rd July 2021 8:51:40 pm
 * @project    stm-utils
 * @brief      Definitions of interrupt vectors for STMF4xx devices
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * /// ============================================================================================================================ */

#ifndef __STM_UTILS_DEVICE_INTERRUPTS_STMF4xx_H__
#define __STM_UTILS_DEVICE_INTERRUPTS_STMF4xx_H__

/* =========================================================== Includes =========================================================== */

#include "interrupts/definitions.h"

/* ========================================================== C mangling ========================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================= Declarations ========================================================= */

extern void SVC_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);

/* ========================================================== Definitions ========================================================= */

/**
 * @note Names for SVC_Handler, PendSV_Handler and SysTick_Handler interrupt
 *    handlers was set differently to fit RTX-RTOSv5 naming scheme
 */

// Exception vector's definitions
ISR_VECTOR       (EXC_NMI);
ISR_VECTOR       (EXC_HardFault);
ISR_VECTOR       (EXC_MemoryManagement);
ISR_VECTOR       (EXC_BusFault);
ISR_VECTOR       (EXC_UsageFault);
ISR_VECTOR_ALIAS (EXC_SVC, "SVC_Handler");
ISR_VECTOR       (EXC_DebugMonitor);
ISR_VECTOR_ALIAS (EXC_PendSV, "PendSV_Handler");
ISR_VECTOR_ALIAS (EXC_SysTick, "SysTick_Handler");

// ISR Vector's definitions
ISR_VECTOR       (ISR_WWDG);
ISR_VECTOR       (ISR_PVD);
ISR_VECTOR       (ISR_Tamper);
ISR_VECTOR       (ISR_RTC_Wakeup);
ISR_VECTOR       (ISR_FLASH);
ISR_VECTOR       (ISR_RCC);
ISR_VECTOR       (ISR_EXTI0);
ISR_VECTOR       (ISR_EXTI1);
ISR_VECTOR       (ISR_EXTI2);
ISR_VECTOR       (ISR_EXTI3);
ISR_VECTOR       (ISR_EXTI4);
ISR_VECTOR       (ISR_DMA1_Stream0);
ISR_VECTOR       (ISR_DMA1_Stream1);
ISR_VECTOR       (ISR_DMA1_Stream2);
ISR_VECTOR       (ISR_DMA1_Stream3);
ISR_VECTOR       (ISR_DMA1_Stream4);
ISR_VECTOR       (ISR_DMA1_Stream5);
ISR_VECTOR       (ISR_DMA1_Stream6);
ISR_VECTOR       (ISR_ADC);
ISR_VECTOR       (ISR_CAN1_TX);
ISR_VECTOR       (ISR_CAN1_RX0);
ISR_VECTOR       (ISR_CAN1_RX1);
ISR_VECTOR       (ISR_CAN1_SCE);
ISR_VECTOR_FORCED(ISR_EXTI9_5);
ISR_VECTOR       (ISR_TIM1_Break_TIM9);
ISR_VECTOR       (ISR_TIM1_Update_TIM10);
ISR_VECTOR       (ISR_TIM1_TRG_COM_TIM11);
ISR_VECTOR       (ISR_TIM1_CC);
ISR_VECTOR       (ISR_TIM2);
ISR_VECTOR       (ISR_TIM3);
ISR_VECTOR       (ISR_TIM4);
ISR_VECTOR       (ISR_I2C1_EV);
ISR_VECTOR       (ISR_I2C1_ER);
ISR_VECTOR       (ISR_I2C2_EV);
ISR_VECTOR       (ISR_I2C2_ER);
ISR_VECTOR       (ISR_SPI1);
ISR_VECTOR       (ISR_SPI2);
ISR_VECTOR       (ISR_USART1);
ISR_VECTOR       (ISR_USART2);
ISR_VECTOR       (ISR_USART3);
ISR_VECTOR_FORCED(ISR_EXTI15_10);
ISR_VECTOR       (ISR_RTC_Alarm);
ISR_VECTOR       (ISR_USB_Wakeup);
ISR_VECTOR       (ISR_TIM8_Break_TIM12);
ISR_VECTOR       (ISR_TIM8_Update_TIM13);
ISR_VECTOR       (ISR_TIM8_TRG_COM_TIM14);
ISR_VECTOR       (ISR_TIM8_CC);
ISR_VECTOR       (ISR_DMA1_Stream7);
ISR_VECTOR       (ISR_FSMC);
ISR_VECTOR       (ISR_SDIO);
ISR_VECTOR       (ISR_TIM5);
ISR_VECTOR       (ISR_SPI3);
ISR_VECTOR       (ISR_USART4);
ISR_VECTOR       (ISR_USART5);
ISR_VECTOR       (ISR_TIM6_DAC);
ISR_VECTOR       (ISR_TIM7);
ISR_VECTOR       (ISR_DMA2_Stream0);
ISR_VECTOR       (ISR_DMA2_Stream1);
ISR_VECTOR       (ISR_DMA2_Stream2);
ISR_VECTOR       (ISR_DMA2_Stream3);
ISR_VECTOR       (ISR_DMA2_Stream4);
ISR_VECTOR       (ISR_ETH);
ISR_VECTOR       (ISR_ETH_Wakeup);
ISR_VECTOR       (ISR_CAN2_TX);
ISR_VECTOR       (ISR_CAN2_RX0);
ISR_VECTOR       (ISR_CAN2_RX1);
ISR_VECTOR       (ISR_CAN2_SCE);
ISR_VECTOR       (ISR_OTG_FS);
ISR_VECTOR       (ISR_DMA2_Stream5);
ISR_VECTOR       (ISR_DMA2_Stream6);
ISR_VECTOR       (ISR_DMA2_Stream7);
ISR_VECTOR       (ISR_USART6);
ISR_VECTOR       (ISR_I2C3_EV);
ISR_VECTOR       (ISR_I2C3_ER);
ISR_VECTOR       (ISR_OTG_HS_EP1_Out);
ISR_VECTOR       (ISR_OTG_HS_Wakeup);
ISR_VECTOR       (ISR_OTG_HS);
ISR_VECTOR       (ISR_DCMI_isr_vector);
ISR_VECTOR       (ISR_Cryp);
ISR_VECTOR       (ISR_Hash_RNG);
ISR_VECTOR       (ISR_FPU);
ISR_VECTOR       (ISR_SPI4);
ISR_VECTOR       (ISR_SPI5);

/* ========================================================= Pseud-vectors ======================================================== */

// Pseudo-ISR vectors
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
