/* ============================================================================================================================= *//**
 * @file       stm32_hal.h
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Friday, 16th July 2021 11:40:45 am
 * @modified   Sunday, 18th July 2021 6:01:23 pm
 * @project    stm-utils
 * @brief      Gathering header file including HAL library for a current target device
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * /// ============================================================================================================================ */

#ifndef __STM_UTILS_HAL_HAL_H__
#define __STM_UTILS_HAL_HAL_H__

/* =========================================================== Includes =========================================================== */

// Include device-specific headers
#if defined(STM32MCU_MAJOR_TYPE_F0)
#include "stm32f0xx_hal.h"
#elif defined(STM32MCU_MAJOR_TYPE_F1)
#include "stm32f1xx_hal.h"
#elif defined(STM32MCU_MAJOR_TYPE_F2)
#include "stm32f2xx_hal.h"
#elif defined(STM32MCU_MAJOR_TYPE_F3)
#include "stm32f3xx_hal.h"
#elif defined(STM32MCU_MAJOR_TYPE_F4)
#include "stm32f4xx_hal.h"
#elif defined(STM32MCU_MAJOR_TYPE_F7)
#include "stm32f7xx_hal.h"
#elif defined(STM32MCU_MAJOR_TYPE_G0)
#include "stm32g0xx_hal.h"
#elif defined(STM32MCU_MAJOR_TYPE_G4)
#include "stm32g4xx_hal.h"
#elif defined(STM32MCU_MAJOR_TYPE_H7)
#include "stm32h7xx_hal.h"
#elif defined(STM32MCU_MAJOR_TYPE_L0)
#include "stm32l0xx_hal.h"
#elif defined(STM32MCU_MAJOR_TYPE_L1)
#include "stm32l1xx_hal.h"
#elif defined(STM32MCU_MAJOR_TYPE_L4)
#include "stm32l4xx_hal.h"
#elif defined(STM32MCU_MAJOR_TYPE_L5)
#include "stm32l5xx_hal.h"
#elif defined(STM32MCU_MAJOR_TYPE_WL)
#include "stm32wlxx_hal.h"
#elif defined(STM32MCU_MAJOR_TYPE_WB)
#include "stm32wbxx_hal.h"
#else
#error Unknown MCU major type
#endif

/* ================================================================================================================================ */

#endif
