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

#ifndef __STM_UTILS_INTERUPT_H__
#define __STM_UTILS_INTERUPT_H__

/* ====================================================== Vectors definitions ===================================================== */

#if defined(STM32MCU_MAJOR_TYPE_F0)
#include "interrupts/stm32f0xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_F1)
#include "interrupts/stm32f1xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_F2)
#include "interrupts/stm32f2xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_F3)
#include "interrupts/stm32f3xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_F4)
#include "interrupts/stm32f4xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_F7)
#include "interrupts/stm32f7xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_G0)
#include "interrupts/stm32g0xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_G4)
#include "interrupts/stm32g4xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_H7)
#include "interrupts/stm32h7xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_L0)
#include "interrupts/stm32l0xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_L1)
#include "interrupts/stm32l1xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_L4)
#include "interrupts/stm32l4xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_L5)
#include "interrupts/stm32l5xx.h"
#else
#error Unknown MCU major type
#endif

/* ================================================================================================================================ */

#endif
