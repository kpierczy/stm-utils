/* ============================================================================================================================= *//**
 * @file       device.h
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 15th July 2021 10:54:42 am
 * @modified   Monday, 19th July 2021 9:16:44 pm
 * @project    stm-utils
 * @brief      Header file gathering CMSIS device header for all STM32 devices
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * /// ============================================================================================================================ */

#ifndef __STM_UTILS_DEVICE_DEVICE_H__
#define __STM_UTILS_DEVICE_DEVICE_H__

/* =========================================================== Includes =========================================================== */

// Include startup header
#include "startup.h"

// Include device-specific headers
#if defined(STM32MCU_MAJOR_TYPE_F0)
#include "device/stm32f0xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_F1)
#include "device/stm32f1xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_F2)
#include "device/stm32f2xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_F3)
#include "device/stm32f3xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_F4)
#include "device/stm32f4xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_F7)
#include "device/stm32f7xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_G0)
#include "device/stm32g0xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_G4)
#include "device/stm32g4xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_H7)
#include "device/stm32h7xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_L0)
#include "device/stm32l0xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_L1)
#include "device/stm32l1xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_L4)
#include "device/stm32l4xx.h"
#elif defined(STM32MCU_MAJOR_TYPE_L5)
#include "device/stm32l5xx.h"
#else
#error Unknown MCU major type
#endif

/* ================================================================================================================================ */

#endif
