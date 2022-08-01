/* ============================================================================================================================= *//**
 * @file       startup.c
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 6th July 2021 1:19:32 pm
 * @modified   Tuesday, 6th July 2021 1:19:37 pm
 * @project    stm-utils
 * @brief      Startup code of the MCU
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * /// ============================================================================================================================ */

/* =========================================================== Includes =========================================================== */

#include "device.h"
#include "startup.h"

/* ========================================================= Declarations ========================================================= */

// Start of the .data section
extern unsigned long _sidata;
// Start of the .data section
extern unsigned long _sdata;
// End of the .data section
extern unsigned long _edata;
// Start of the .bss section
extern unsigned long _sbss;
// End of the .bss section
extern unsigned long _ebss;

// Application's entrypoint
extern int main(void);
// Libc routines
extern void __libc_init_array(void);
extern void __libc_fini_array(void);

/* ====================================================== Static definitions ====================================================== */

/**
 * @brief Setups basic functions of the Core
 */
static void earlyCpuSetup(void) {

	// Enable FPU if present
    #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
        SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));  // set CP10 and CP11 Full Access
    #endif
    
	// // Trap divide by zero
    // SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk | SCB_CCR_STKALIGN_Msk;

}

/* ========================================================== Definitions ========================================================= */

void stubFunction() { }

void startupExtension(void) __attribute__ ((weak, alias("stubFunction")));

void exitExtension(void) __attribute__ ((weak, alias("stubFunction")));

void resetHandler(void) {

	// Initialize basic functions of CPU
	earlyCpuSetup();

    // Copy the data segment initializers from flash to SRAM.
    for(unsigned long *src = &_sidata, *dst = &_sdata; dst < &_edata; )
        *(dst++) = *(src++);

    // Zero fill the bss segment
    for(unsigned long *dst = &_sbss; dst < &_ebss; )
        *(dst++) = 0;

    // Call external startup code before construtors call
    startupExtension();

    // Call constructors
    __libc_init_array();

    // Call the application's entry point
    main();

    // Call destructors
    __libc_fini_array();

	// Callexternal exit routine
    exitExtension();
    
    while(1);
}

/* ================================================================================================================================ */