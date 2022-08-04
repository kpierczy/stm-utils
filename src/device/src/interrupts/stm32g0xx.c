/* ============================================================================================================================= *//**
 * @file       stm32g0xx.c
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 6th July 2021 1:51:11 pm
 * @modified   Tuesday, 6th July 2021 1:51:11 pm
 * @project    stm-utils
 * @brief      Interrupt vectors' definitions for STMG0xx devices
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * /// ============================================================================================================================ */

/* =========================================================== Includes =========================================================== */

#include "device.h"
#include "interrupts.h"

/* ================================================= Emulated vectors definitions ================================================= */

// Dispatcher of the EXTI 0-1 lines
void ISR_EXTI0_1(void) {

    // Get EXTI pending flags
	unsigned long flags = (EXTI->RPR1 | EXTI->FPR1);

    // Dispatch lines
	if(ExtiPends(flags, 0))
		ISR_EXTI0();
	if(ExtiPends(flags, 1))
		ISR_EXTI1();
}

// Dispatcher of the EXTI 2-3 lines
void ISR_EXTI2_3(void) {

    // Get EXTI pending flags
	unsigned long flags = (EXTI->RPR1 | EXTI->FPR1);

    // Dispatch lines
	if(ExtiPends(flags, 2))
		ISR_EXTI2();
	if(ExtiPends(flags, 3))
		ISR_EXTI3();
}

// Dispatcher of the EXTI 4-5 lines
void ISR_EXTI4_15(void) {
	
    // Get EXTI pending flags
	unsigned long flags = (EXTI->RPR1 | EXTI->FPR1);

    // Dispatch lines
	if(ExtiPends(flags, 4))
		ISR_EXTI4();
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

const VectorFunctionPtr isr_vectors_table[] __attribute__((section(".isr_vector"))) = {

    // Stack pointer
    (VectorFunctionPtr) (long) &_estack,
    // Reset handler
    reser_handler,

    /* ----------------------------- Exception vectors ----------------------------- */    

    EXC_NMI,
    EXC_HardFault,
    EXC_MemoryManagement,
    0,
    0,
    0,
    0,
    0,
    0,
    SVC_Handler,
    0,
    0,
    PendSV_Handler,
    SysTick_Handler,

    /* ----------------------------- Interrupt vectors ----------------------------- */

    ISR_WWDG,
    0,
    ISR_RTC_TAMP,
    ISR_FLASH,
    ISR_RCC,
    ISR_EXTI0_1,
    ISR_EXTI2_3,
    ISR_EXTI4_15,
    0,
    ISR_DMA1_Channel1,
    ISR_DMA1_Channel2_3,
    ISR_DMA1_Ch4_5_DMAMUX1_OVR,
    ISR_ADC1,
    ISR_TIM1_BRK_UP_TRG_COM,
    ISR_TIM1_CC,
    0,
    ISR_TIM3,
    0,
    0,
    ISR_TIM14,
    0,
    ISR_TIM16,
    ISR_TIM17,
    ISR_I2C1,
    ISR_I2C2,
    ISR_SPI1,
    ISR_SPI2,
    ISR_USART1,
    ISR_USART2,
    0
};

/* ================================================================================================================================ */
