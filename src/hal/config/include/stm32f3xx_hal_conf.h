/* ============================================================================================================================= *//**
 * @file       stm32f3xx_hal_conf_template.h
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Friday, 16th July 2021 11:26:29 am
 * @modified   Friday, 16th July 2021 2:17:31 pm
 * @project    stm-utils
 * @brief      HAL configuration header for STM32F3xx devices
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * /// ============================================================================================================================ */

#ifndef __STM_UTILS_HAL_CONFIG_STM32F3xx_H__
#define __STM_UTILS_HAL_CONFIG_STM32F3xx_H__

/* =========================================================== Includes =========================================================== */

#include "hal_config.h"
#include "stm32f3xx_hal_def.h"

/* ========================================================= HAL Includes ========================================================= */

#ifdef HAL_RCC_MODULE_ENABLED
#include "stm32f3xx_hal_rcc.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
#include "stm32f3xx_hal_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

#ifdef HAL_EXTI_MODULE_ENABLED
#include "stm32f3xx_hal_exti.h"
#endif /* HAL_EXTI_MODULE_ENABLED */

#ifdef HAL_DMA_MODULE_ENABLED
#include "stm32f3xx_hal_dma.h"
#endif /* HAL_DMA_MODULE_ENABLED */
   
#ifdef HAL_CORTEX_MODULE_ENABLED
#include "stm32f3xx_hal_cortex.h"
#endif /* HAL_CORTEX_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
#include "stm32f3xx_hal_adc.h"
#endif /* HAL_ADC_MODULE_ENABLED */

#ifdef HAL_CAN_MODULE_ENABLED
#include "stm32f3xx_hal_can.h"
#endif /* HAL_CAN_MODULE_ENABLED */

#ifdef HAL_CAN_LEGACY_MODULE_ENABLED
#include "stm32f3xx_hal_can_legacy.h"
#endif /* HAL_CAN_LEGACY_MODULE_ENABLED */

#ifdef HAL_CEC_MODULE_ENABLED
#include "stm32f3xx_hal_cec.h"
#endif /* HAL_CEC_MODULE_ENABLED */

#ifdef HAL_COMP_MODULE_ENABLED
#include "stm32f3xx_hal_comp.h"
#endif /* HAL_COMP_MODULE_ENABLED */

#ifdef HAL_CRC_MODULE_ENABLED
#include "stm32f3xx_hal_crc.h"
#endif /* HAL_CRC_MODULE_ENABLED */

#ifdef HAL_DAC_MODULE_ENABLED
#include "stm32f3xx_hal_dac.h"
#endif /* HAL_DAC_MODULE_ENABLED */

#ifdef HAL_FLASH_MODULE_ENABLED
#include "stm32f3xx_hal_flash.h"
#endif /* HAL_FLASH_MODULE_ENABLED */

#ifdef HAL_SRAM_MODULE_ENABLED
#include "stm32f3xx_hal_sram.h"
#endif /* HAL_SRAM_MODULE_ENABLED */

#ifdef HAL_NOR_MODULE_ENABLED
#include "stm32f3xx_hal_nor.h"
#endif /* HAL_NOR_MODULE_ENABLED */

#ifdef HAL_NAND_MODULE_ENABLED
#include "stm32f3xx_hal_nand.h"
#endif /* HAL_NAND_MODULE_ENABLED */

#ifdef HAL_PCCARD_MODULE_ENABLED
#include "stm32f3xx_hal_pccard.h"
#endif /* HAL_PCCARD_MODULE_ENABLED */ 
  
#ifdef HAL_HRTIM_MODULE_ENABLED
#include "stm32f3xx_hal_hrtim.h"
#endif /* HAL_HRTIM_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
#include "stm32f3xx_hal_i2c.h"
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_I2S_MODULE_ENABLED
#include "stm32f3xx_hal_i2s.h"
#endif /* HAL_I2S_MODULE_ENABLED */

#ifdef HAL_IRDA_MODULE_ENABLED
#include "stm32f3xx_hal_irda.h"
#endif /* HAL_IRDA_MODULE_ENABLED */

#ifdef HAL_IWDG_MODULE_ENABLED
#include "stm32f3xx_hal_iwdg.h"
#endif /* HAL_IWDG_MODULE_ENABLED */

#ifdef HAL_OPAMP_MODULE_ENABLED
#include "stm32f3xx_hal_opamp.h"
#endif /* HAL_OPAMP_MODULE_ENABLED */

#ifdef HAL_PCD_MODULE_ENABLED
#include "stm32f3xx_hal_pcd.h"
#endif /* HAL_PCD_MODULE_ENABLED */

#ifdef HAL_PWR_MODULE_ENABLED
#include "stm32f3xx_hal_pwr.h"
#endif /* HAL_PWR_MODULE_ENABLED */

#ifdef HAL_RTC_MODULE_ENABLED
#include "stm32f3xx_hal_rtc.h"
#endif /* HAL_RTC_MODULE_ENABLED */

#ifdef HAL_SDADC_MODULE_ENABLED
#include "stm32f3xx_hal_sdadc.h"
#endif /* HAL_SDADC_MODULE_ENABLED */

#ifdef HAL_SMARTCARD_MODULE_ENABLED
#include "stm32f3xx_hal_smartcard.h"
#endif /* HAL_SMARTCARD_MODULE_ENABLED */

#ifdef HAL_SMBUS_MODULE_ENABLED
#include "stm32f3xx_hal_smbus.h"
#endif /* HAL_SMBUS_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
#include "stm32f3xx_hal_spi.h"
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_TIM_MODULE_ENABLED
#include "stm32f3xx_hal_tim.h"
#endif /* HAL_TIM_MODULE_ENABLED */

#ifdef HAL_TSC_MODULE_ENABLED
#include "stm32f3xx_hal_tsc.h"
#endif /* HAL_TSC_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
#include "stm32f3xx_hal_uart.h"
#endif /* HAL_UART_MODULE_ENABLED */

#ifdef HAL_USART_MODULE_ENABLED
#include "stm32f3xx_hal_usart.h"
#endif /* HAL_USART_MODULE_ENABLED */

#ifdef HAL_WWDG_MODULE_ENABLED
#include "stm32f3xx_hal_wwdg.h"
#endif /* HAL_WWDG_MODULE_ENABLED */

/* ================================================================================================================================ */

#endif