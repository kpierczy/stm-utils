/* ============================================================================================================================= *//**
 * @file       stm32wlxx.cpp
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

// System includes
#include "device/interrupts.h"

/* ======================================================= Helper functions ======================================================= */

extern "C" IRQn_Type get_exti_line_irqn(unsigned index) {
    switch(index) {
        case 0:
            return EXTI0_IRQn;
        case 1:
            return EXTI1_IRQn;
        case 2:
            return EXTI2_IRQn;
        case 3:
            return EXTI3_IRQn;
        case 4:
            return EXTI4_IRQn;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            return EXTI9_5_IRQn;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            return EXTI15_10_IRQn;
        default:
            return (IRQn_Type) 0xFFFFFFFF;
    }
}

/* =========================================================== Namespace ========================================================== */

namespace device {

/* ======================================================= Helper functions ======================================================= */

std::optional<IRQn_Type> get_exti_line_irqn(unsigned index) {
    switch(index) {
        case 0:
            return EXTI0_IRQn;
        case 1:
            return EXTI1_IRQn;
        case 2:
            return EXTI2_IRQn;
        case 3:
            return EXTI3_IRQn;
        case 4:
            return EXTI4_IRQn;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            return EXTI9_5_IRQn;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            return EXTI15_10_IRQn;
        default:
            return std::optional<IRQn_Type>{ };
    }
}

/* ================================================================================================================================ */

}

/* ================================================================================================================================ */
