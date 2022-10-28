/* ============================================================================================================================= *//**
 * @file       stm32f4xx.c
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 6th July 2021 1:51:11 pm
 * @modified   Tuesday, 6th July 2021 1:51:11 pm
 * @project    stm-utils
 * @brief      Definitions of interrupt vectors for STMF4xx devices
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * /// ============================================================================================================================ */

/* =========================================================== Includes =========================================================== */

#include "device.h"
#include "interrupts/definitions.h"

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
ISR_VECTOR       (SVC_Handler);
ISR_VECTOR       (EXC_DebugMonitor);
ISR_VECTOR       (PendSV_Handler);
ISR_VECTOR       (SysTick_Handler);

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

/* ================================================= Emulated vectors definitions ================================================= */

// Dispatcher of the EXTI 5-9 lines
void ISR_EXTI9_5(void) {

    // Get EXTI pending flags
	unsigned long flags = EXTI->PR;

    // Dispatch lines
	if(ExtiPends(flags, 5))
		ISR_EXTI5();
	if(ExtiPends(flags, 6))
		ISR_EXTI6();
	if(ExtiPends(flags, 7))
		ISR_EXTI7();
	if(ExtiPends(flags, 8))
		ISR_EXTI8();
	if(ExtiPends(flags, 9))
		ISR_EXTI9();
}

// Dispatcher of the EXTI 10-15 lines
void ISR_EXTI15_10(void) {
	
    // Get EXTI pending flags
	unsigned long flags = EXTI->PR;

    // Dispatch lines
	if(ExtiPends(flags, 10))
		ISR_EXTI10();
	if(ExtiPends(flags, 11))
		ISR_EXTI11();
	if(ExtiPends(flags, 12))
		ISR_EXTI12();
	if(ExtiPends(flags, 13))
		ISR_EXTI13();
	if(ExtiPends(flags, 14))
		ISR_EXTI14();
	if(ExtiPends(flags, 15))
		ISR_EXTI15();
}

/* ======================================================== Vectors' table ======================================================== */

const vector_function_ptr isr_vectors_table[] __attribute__((section(".isr_vector"))) = {

    // Stack pointer
    (vector_function_ptr) (long) &_estack,
    // Reset handler
    reser_handler,

    /* ----------------------------- Exception vectors ----------------------------- */    

    EXC_NMI,
    EXC_HardFault,
    EXC_MemoryManagement,
    EXC_BusFault,
    EXC_UsageFault,
    0,
    0,
    0,
    0,
    SVC_Handler,
    EXC_DebugMonitor,
    0,
    PendSV_Handler,
    SysTick_Handler,

    /* ----------------------------- Interrupt vectors ----------------------------- */

    ISR_WWDG,
    ISR_PVD,
    ISR_Tamper,
    ISR_RTC_Wakeup,
    ISR_FLASH,
    ISR_RCC,
    ISR_EXTI0,
    ISR_EXTI1,
    ISR_EXTI2,
    ISR_EXTI3,
    ISR_EXTI4,
    ISR_DMA1_Stream0,
    ISR_DMA1_Stream1,
    ISR_DMA1_Stream2,
    ISR_DMA1_Stream3,
    ISR_DMA1_Stream4,
    ISR_DMA1_Stream5,
    ISR_DMA1_Stream6,
    ISR_ADC,
    ISR_CAN1_TX,
    ISR_CAN1_RX0,
    ISR_CAN1_RX1,
    ISR_CAN1_SCE,
    ISR_EXTI9_5,
    ISR_TIM1_Break_TIM9,
    ISR_TIM1_Update_TIM10,
    ISR_TIM1_TRG_COM_TIM11,
    ISR_TIM1_CC,
    ISR_TIM2,
    ISR_TIM3,
    ISR_TIM4,
    ISR_I2C1_EV,
    ISR_I2C1_ER,
    ISR_I2C2_EV,
    ISR_I2C2_ER,
    ISR_SPI1,
    ISR_SPI2,
    ISR_USART1,
    ISR_USART2,
    ISR_USART3,
    ISR_EXTI15_10,	
    ISR_RTC_Alarm,
    ISR_USB_Wakeup,
    ISR_TIM8_Break_TIM12,
    ISR_TIM8_Update_TIM13,
    ISR_TIM8_TRG_COM_TIM14,
    ISR_TIM8_CC,
    ISR_DMA1_Stream7,
    ISR_FSMC,
    ISR_SDIO,
    ISR_TIM5,
    ISR_SPI3,
    ISR_USART4,
    ISR_USART5,
    ISR_TIM6_DAC,
    ISR_TIM7,
    ISR_DMA2_Stream0,
    ISR_DMA2_Stream1,
    ISR_DMA2_Stream2,
    ISR_DMA2_Stream3,
    ISR_DMA2_Stream4,
    ISR_ETH,
    ISR_ETH_Wakeup,
    ISR_CAN2_TX,
    ISR_CAN2_RX0,
    ISR_CAN2_RX1,
    ISR_CAN2_SCE,
    ISR_OTG_FS,
    ISR_DMA2_Stream5,
    ISR_DMA2_Stream6,
    ISR_DMA2_Stream7,
    ISR_USART6,
    ISR_I2C3_EV,
    ISR_I2C3_ER,
    ISR_OTG_HS_EP1_Out,
    ISR_OTG_HS_EP1_Out,
    ISR_OTG_HS_Wakeup,
    ISR_OTG_HS,
    ISR_DCMI_isr_vector,
    ISR_Cryp,
    ISR_Hash_RNG,
    ISR_FPU,
    0,
    0,
    ISR_SPI4,
    ISR_SPI5
};

/* ================================================================================================================================ */
