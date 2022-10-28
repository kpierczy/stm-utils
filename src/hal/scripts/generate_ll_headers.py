# ====================================================================================================================================
# @file       parse.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Friday, 16th July 2021 10:17:57 am
# @modified   Friday, 28th October 2022 10:52:52 pm
# @project    stm-utils
# @brief      Generates universal headers for LL library for all possible STM32 targets
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

import sys
import os
from datetime import datetime

# ========================================================== Configuration ========================================================= #

# Path to the main project's dircetory
PROJECT_HOME = os.path.join(os.path.dirname(os.path.realpath(__file__)), '../../..')

# Add python module to the PATH containing links definitions
sys.path.append(os.path.join(PROJECT_HOME, 'scripts'))

# ============================================================ Imports ============================================================= #

from Cheetah.Template import Template
import os
import utils
import codecs

# ============================================================= Helpers ============================================================ #

def add_ordinal(n):
    return str(n) + ("th" if (4 <= n % 100 <= 20) else { 1: "st", 2 : "nd", 3 : "rd"}.get(n % 10, "th"))

def format_datetime(dt):
    return dt.strftime("%A, " + add_ordinal(dt.day) + " %B %Y %X ") + dt.strftime('%p').lower()

# ============================================================ Template ============================================================ #

template = u"""/* ============================================================================================================================= *//**
 * @file       stm32_ll_${lib}.h
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       ${datetime}
 * @modified   ${datetime}
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
families = [x.upper() for x in utils.config.SUPPORTED_FAMILIES ]

# List of libraries to generate headers for (pairs "libname" : "description")
libraries = {
    "adc"        : "ADC (Analog to Digital Converter)",
    "bdma"       : "Basic DMA (Direct Memory Access)",
    "bus"        : "System bus",
    "comp"       : "Analog comparator",
    "cordic"     : "Cordic Coprocessor",
    "cortex"     : "CPU core",
    "crc"        : "CRC (Cyclic Redundancy Check)",
    "crs"        : "CRS (Clock Recovery System)",
    "dac"        : "DAC (Digital to Analog Converter)",
    "delayblock" : "Hardware delay block",
    "dma2d"      : "DMA (Direct Memory Access) 2D",
    "dma"        : "DMA (Direct Memory Access)",
    "dmamux"     : "DMAMUX (Direct Memory Access Requests Multiplexer)",
    "hsem"       : "Hardware semaphore",
    "hrtim"      : "HRTIM (High-resolution Timer)",
    "exti"       : "EXTI (External Interrupt)",
    "fmac"       : "FMAC (Filter Math Accelerator)",
    "fmc"        : "FMC (Flash Memory Interface)",
    "fmpi2c"     : "FMPI2C (Fast Module Pulse I2C)",
    "fsmc"       : "FSMC (Flexible Static Memory Controller)",
    "gpio"       : "GPIO (Generl Port Input/Output)",
    "i2c"        : "I2C interface",
    "ipcc"       : "Inter-processor communication controller",
    "iwdg"       : "IWDG (Independent Watchdog)",
    "lptim"      : "LPTIM (Low Power Timer)",
    "lpuart"     : "LPUART (Low Power UART)",
    "mdma"       : "Master DMA (Direct Access Memory)",
    "opamp"      : "OPAMP (Operational Amplifier)",
    "pka"        : "Public Key Accelerator",
    "pwr"        : "Power",
    "rcc"        : "RCC (Reset & Clock Control)",
    "rng"        : "RNG (Random Number Generator)",
    "rtc"        : "RTC (Real Time Clock)",
    "sdmmc"      : "SDMMC (Secure Digital Multimedia Card)",
    "spi"        : "SPI interface",
    "system"     : "System",
    "swpmi"      : "SWPMI (Single-wire Protocol Master Interface)",
    "tim"        : "timer",
    "ucpd"       : "UPCD (USB Type C / Power Delivery)",
    "usart"      : "USART interface",
    "usb"        : "USB interface",
    "utils"      : "utilities",
    "wwdg"       : "WWDG (Windowed Watchdog)"
}

# Generation namespace
namespace = {
    "families"        : families,
    "lib"             : "",
    "lib_description" : "",
    "datetime"        : format_datetime(datetime.now()),
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
    with codecs.open(path, 'w', 'utf-8') as f:
        f.write(str(t))
