# ====================================================================================================================================
# @file       parse.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Friday, 16th July 2021 10:17:57 am
# @modified   Tuesday, 30th August 2022 11:06:27 am
# @project    stm-utils
# @brief      Generates universal headers for LL library for all possible STM32 targets
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

from Cheetah.Template import Template
import os

# ============================================================ Template ============================================================ #

template = """/* ============================================================================================================================= *//**
 * @file       stm32_ll_${lib}.h
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Sunday, 18th July 2021 4:42:07 pm
 * @modified   Monday, 19th July 2021 4:59:58 pm
 * @project    stm-utils
 * @brief      Aggregating header file for STM32 ${lib_description} Low Level library
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * /// ============================================================================================================================ */

\#ifndef __STM_UTILS_HAL_LL_${lib.upper()}_H__
\#define __STM_UTILS_HAL_LL_${lib.upper()}_H__

/* =========================================================== Includes =========================================================== */

\#if defined(STM32MCU_MAJOR_TYPE_${families[0].upper()})
\#include "stm32f0xx_ll_${lib}.h"
#for i in range(1, len($families)):
\#elif defined(STM32MCU_MAJOR_TYPE_${families[$i].upper()})
\#include "stm32${families[$i].lower()}xx_ll_${lib}.h"
#end for
\#else
\#error Unknown MCU major type
\#endif

/* ================================================================================================================================ */

\#endif
"""

# ========================================================== Dictionaries ========================================================== #

# List o families to generate for
families = [ "F0", "F1", "F2", "F3", "F4", "F7", "G0", "G4", "H7", "L0", "L1", "L4", "L5" ]

# List of libraries to generate headers for (pairs "libname" : "description")
libraries = {
    "adc"    : "ADC (Analog to Digital Converter)",
    "bus"    : "system bus",
    "cortex" : "CPU core",
    "crc"    : "CRC (Cyclic Redundancy Check)",
    "dac"    : "DAC (Digital to Analog Converter)",
    "dma2d"  : "DMA (Direct Memory Access) 2D",
    "dma"    : "DMA (Direct Memory Access)",
    "dmamux" : "DMAMUX (Direct Memory Access Requests Multiplexer)",
    "exti"   : "EXTI (External Interrupt)",
    "fmc"    : "FMC (Flash Memory Interface)",
    "fmpi2c" : "FMPI2C (Fast Module Pulse I2C)",
    "fsmc"   : "FSMC (Flexible Static Memory Controller)",
    "gpio"   : "GPIO (Generl Port Input/Output)",
    "i2c"    : "I2C interface",
    "iwdg"   : "IWDG (Independent Watchdog)",
    "lptim"  : "LPTIM (Low Power Timer)",
    "pwr"    : "power",
    "rcc"    : "RCC (Reset & Clock Control)",
    "rng"    : "RNG (Random Number Generator)",
    "rtc"    : "RTC (Real Time Clock)",
    "sdmmc"  : "SDMMC (Secure Digital Multimedia Card)",
    "spi"    : "SPI interface",
    "system" : "system",
    "tim"    : "timer",
    "usart"  : "USART interface",
    "usb"    : "USB interface",
    "utils"  : "utilities",
    "wwdg"   : "WWDG (Windowed Watchdog)"
}

# Generation namespace
namespace = {
    "families"        : families,
    "lib"             : "",
    "lib_description" : "",
}

# ============================================================== Code ============================================================== #

# Calculate package home
PACKAGE_HOME = os.path.join(os.path.dirname(os.path.realpath(__file__)), '..')

# Iterate over all libraries to be generated
for key, value in libraries.items():

    # Generate output path for the header file
    path = os.path.join(PACKAGE_HOME, 'include/ll/stm32_ll_' + key + '.h')

    # Remove file if already exists
    if os.path.exists(path):
        os.remove(path)

    # Fill namespace
    namespace["lib"]             = key
    namespace["lib_description"] = value

    # Generate template
    t = Template(template, searchList=[namespace])

    # Write template to file
    with open(path, 'w') as f:
        f.write(str(t))
