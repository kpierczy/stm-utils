/* ============================================================================================================================= *//**
 * @file       RTE_Components.h
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 15th July 2021 7:38:14 am
 * @modified   Friday, 16th July 2021 2:46:12 pm
 * @project    stm-utils
 * @brief      Header file used to configure RTE (Run-Time Environment) components (e.g. drivers, file systems, EVR)
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * /// ============================================================================================================================ */

#ifndef __RTE_COMPONENTS_H__
#define __RTE_COMPONENTS_H__

/* ========================================================== Definitions ========================================================= */

// RTOS-related defines (found these in ARM docs, not sure they influence much...)
#define RTE_CMSIS_RTOS
#define RTE_CMSIS_RTOS_RTX5

// Event Recorder (not needed at the moment)
#ifndef EVR_RTX_DISABLE
#define EVR_RTX_DISABLE
#endif

/* ================================================================================================================================ */


#endif
