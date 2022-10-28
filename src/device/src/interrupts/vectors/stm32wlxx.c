/* ============================================================================================================================= *//**
 * @file       stm32wlxx.c
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 6th July 2021 1:51:11 pm
 * @modified   Tuesday, 6th July 2021 1:51:11 pm
 * @project    stm-utils
 * @brief      Definitions of interrupt vectors for STMWLxx devices
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
ISR_VECTOR       (EXC_UageFault);
ISR_VECTOR       (SVC_Handler);
ISR_VECTOR       (DebugMon_Handler);
ISR_VECTOR       (PendSV_Handler);
ISR_VECTOR       (SysTick_Handler);

// ISR Vector's definitions
ISR_VECTOR       (ISR_WWDG);
ISR_VECTOR       (ISR_PVD_PVM);
ISR_VECTOR       (ISR_TAMP_STAMP_LSECSS_SSRU);
ISR_VECTOR       (ISR_RTC_WKUP);
ISR_VECTOR       (ISR_FLASH);
ISR_VECTOR       (ISR_RCC);
ISR_VECTOR       (ISR_EXTI0);
ISR_VECTOR       (ISR_EXTI1);
ISR_VECTOR       (ISR_EXTI2);
ISR_VECTOR       (ISR_EXTI3);
ISR_VECTOR       (ISR_EXTI4);
ISR_VECTOR       (ISR_DMA1_Channel1);
ISR_VECTOR       (ISR_DMA1_Channel2);
ISR_VECTOR       (ISR_DMA1_Channel3);
ISR_VECTOR       (ISR_DMA1_Channel4);
ISR_VECTOR       (ISR_DMA1_Channel5);
ISR_VECTOR       (ISR_DMA1_Channel6);
ISR_VECTOR       (ISR_DMA1_Channel7);
ISR_VECTOR       (ISR_ADC);
ISR_VECTOR       (ISR_DAC);
ISR_VECTOR       (ISR_C2SEV_PWR_C2H);
ISR_VECTOR       (ISR_COMP);
ISR_VECTOR_FORCED(ISR_EXTI9_5);
ISR_VECTOR       (ISR_TIM1_BRK);
ISR_VECTOR       (ISR_TIM1_UP);
ISR_VECTOR       (ISR_TIM1_TRG_COM);
ISR_VECTOR       (ISR_TIM1_CC);
ISR_VECTOR       (ISR_TIM2);
ISR_VECTOR       (ISR_TIM16);
ISR_VECTOR       (ISR_TIM17);
ISR_VECTOR       (ISR_I2C1_EV);
ISR_VECTOR       (ISR_I2C1_ER);
ISR_VECTOR       (ISR_I2C2_EV);
ISR_VECTOR       (ISR_I2C2_ER);
ISR_VECTOR       (ISR_SPI1);
ISR_VECTOR       (ISR_SPI2);
ISR_VECTOR       (ISR_USART1);
ISR_VECTOR       (ISR_USART2);
ISR_VECTOR       (ISR_LPUART1);
ISR_VECTOR       (ISR_LPTIM1);
ISR_VECTOR       (ISR_LPTIM2);
ISR_VECTOR_FORCED(ISR_EXTI15_10);
ISR_VECTOR       (ISR_RTC_Alarm);
ISR_VECTOR       (ISR_LPTIM3);
ISR_VECTOR       (ISR_SUBGHZSPI);
ISR_VECTOR       (ISR_IPCC_C1_RX);
ISR_VECTOR       (ISR_IPCC_C1_TX);
ISR_VECTOR       (ISR_HSEM);
ISR_VECTOR       (ISR_I2C3_EV);
ISR_VECTOR       (ISR_I2C3_ER);
ISR_VECTOR       (ISR_SUBGHZ_Radio);
ISR_VECTOR       (ISR_AES);
ISR_VECTOR       (ISR_RNG);
ISR_VECTOR       (ISR_PKA);
ISR_VECTOR       (ISR_DMA2_Channel1);
ISR_VECTOR       (ISR_DMA2_Channel2);
ISR_VECTOR       (ISR_DMA2_Channel3);
ISR_VECTOR       (ISR_DMA2_Channel4);
ISR_VECTOR       (ISR_DMA2_Channel5);
ISR_VECTOR       (ISR_DMA2_Channel6);
ISR_VECTOR       (ISR_DMA2_Channel7);
ISR_VECTOR       (ISR_DMAMUX1_OVR);

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

// Dispatcher of the EXTI 10-15 lines
void ISR_EXTI9_5(void) {
	
    // Get EXTI pending flags
	unsigned long flags = (EXTI->PR1);

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
	unsigned long flags = (EXTI->PR1);

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

    /**
     * @note Exception vector No. -6 is reserved by ARM. It is not used in
     *    Cortex-M0 cores. Here, the vector is used to store address of the
     *    memory section storing version data of the firmware.
     */

    EXC_NMI,
    EXC_HardFault,
    EXC_MemoryManagement,
    EXC_BusFault,
    EXC_UageFault,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,

    /* ----------------------------- Interrupt vectors ----------------------------- */

    ISR_WWDG,
    ISR_PVD_PVM,
    ISR_TAMP_STAMP_LSECSS_SSRU,
    ISR_RTC_WKUP,
    ISR_FLASH,
    ISR_RCC,
    ISR_EXTI0,
    ISR_EXTI1,
    ISR_EXTI2,
    ISR_EXTI3,
    ISR_EXTI4,
    ISR_DMA1_Channel1,
    ISR_DMA1_Channel2,
    ISR_DMA1_Channel3,
    ISR_DMA1_Channel4,
    ISR_DMA1_Channel5,
    ISR_DMA1_Channel6,
    ISR_DMA1_Channel7,
    ISR_ADC,
    ISR_DAC,
    ISR_C2SEV_PWR_C2H,
    ISR_COMP,
    ISR_EXTI9_5,
    ISR_TIM1_BRK,
    ISR_TIM1_UP,
    ISR_TIM1_TRG_COM,
    ISR_TIM1_CC,
    ISR_TIM2,
    ISR_TIM16,
    ISR_TIM17,
    ISR_I2C1_EV,
    ISR_I2C1_ER,
    ISR_I2C2_EV,
    ISR_I2C2_ER,
    ISR_SPI1,
    ISR_SPI2,
    ISR_USART1,
    ISR_USART2,
    ISR_LPUART1,
    ISR_LPTIM1,
    ISR_LPTIM2,
    ISR_EXTI15_10,
    ISR_RTC_Alarm,
    ISR_LPTIM3,
    ISR_SUBGHZSPI,
    ISR_IPCC_C1_RX,
    ISR_IPCC_C1_TX,
    ISR_HSEM,
    ISR_I2C3_EV,
    ISR_I2C3_ER,
    ISR_SUBGHZ_Radio,
    ISR_AES,
    ISR_RNG,
    ISR_PKA,
    ISR_DMA2_Channel1,
    ISR_DMA2_Channel2,
    ISR_DMA2_Channel3,
    ISR_DMA2_Channel4,
    ISR_DMA2_Channel5,
    ISR_DMA2_Channel6,
    ISR_DMA2_Channel7,
    ISR_DMAMUX1_OVR,
};

/* ================================================================================================================================ */
