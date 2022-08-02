/* ============================================================================================================================= *//**
 * @file       hal_config.h
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Friday, 16th July 2021 9:52:30 am
 * @modified   Friday, 23rd July 2021 7:55:12 pm
 * @project    stm-utils
 * @brief      Configuration file of the HAL library
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * /// ============================================================================================================================ */

#ifndef __STM_UTILS_HAL_CONFIG_H__
#define __STM_UTILS_HAL_CONFIG_H__

/* =========================================================== Includes =========================================================== */

#include "stdint.h"

/* ====================================================== System informations ===================================================== */

// Value of VDD in [mV]
#define VDD_VALUE 3300U

// Tick interrupt priority (lowest by default)
#define TICK_INT_PRIORITY ((uint32_t)(1U << __NVIC_PRIO_BITS) - 1U) 

// HAL assert usage
#define USE_FULL_ASSERT

// Information about RTOS usage
#define USE_RTOS 0U
// FLASH prefetch enable flag
#define PREFETCH_ENABLE 0U
// Instruction cache enable flag
#define INSTRUCTION_CACHE_ENABLE 0U
// Data cache enable flag
#define DATA_CACHE_ENABLE 0U

// FLASH preread enable flag (L0 device-specific)
#define PREREAD_ENABLE 0U
// FLASH buffer cache enable flag (L0 device-specific)
#define BUFFER_CACHE_DISABLE 0U

/* ================================================== System clocks' informations ================================================= */

// Speed of the External High-Speed oscillator in [Hz]
#define HSE_VALUE 8000000UL
// Timeout for HSE start up in [ms]
#define HSE_STARTUP_TIMEOUT 100UL

// Speed of the Internal High-Speed oscillator in [Hz]
#define HSI_VALUE 16000000UL
// Timeout for HSI start up in [ms]
#define HSI_STARTUP_TIMEOUT 5000UL

// Speed of the Internal Low-Speed oscillator in [Hz]
#define LSI_VALUE 32000UL
// Timeout for LSI start up in [ms]
#define LSI_STARTUP_TIMEOUT 5000UL

// Speed of the External Low-Speed oscillator in [Hz]
#define LSE_VALUE 32768UL
// Timeout for LSE start up in [ms]
#define LSE_STARTUP_TIMEOUT 5000UL

// Speed of the Internal High-Speed oscillator for ADC in [Hz]
#define HSI14_VALUE 14000000UL
// Speed of the Internal High-Speed oscillator for USB in [Hz]
#define HSI48_VALUE 48000000UL
// External clock source for I2S peripheral (where applicable)
#define EXTERNAL_I2S1_CLOCK_VALUE 12288000UL
#define EXTERNAL_I2S2_CLOCK_VALUE    48000UL
#define EXTERNAL_CLOCK_VALUE EXTERNAL_I2S1_CLOCK_VALUE
// Value of the SAI1 External clock source in [Hz]
#define EXTERNAL_SAI1_CLOCK_VALUE 48000UL
// Value of the SAI2 External clock source in [Hz]
#define EXTERNAL_SAI2_CLOCK_VALUE 48000UL

/* ==================================================== Ethernet configuration ==================================================== */

/* ------------- Section 1 : Ethernet peripheral configuration ------------- */

// MAC address bytes configuration
#define MAC_ADDR0 2U
#define MAC_ADDR1 0U
#define MAC_ADDR2 0U
#define MAC_ADDR3 0U
#define MAC_ADDR4 0U
#define MAC_ADDR5 0U

// Buffer size for receive
#define ETH_RX_BUF_SIZE ETH_MAX_PACKET_SIZE
// Buffer size for transmit
#define ETH_TX_BUF_SIZE ETH_MAX_PACKET_SIZE
// Number of RX buffers of size ETH_RX_BUF_SIZE
#define ETH_RXBUFNB 4U
// Number of TX buffers of size ETH_TX_BUF_SIZE
#define ETH_TXBUFNB 4U

/* ----------------- Section 2: PHY configuration section ----------------- */

// DP83848 PHY Address
#define DP83848_PHY_ADDRESS 0x01U
// PHY Reset delay (based on a 1 ms Systick interrupts)
#define PHY_RESET_DELAY 0x000000FFU
// PHY Configuration delay (based on a 1 ms Systick interrupts)
#define PHY_CONFIG_DELAY 0x00000FFFU

#define PHY_READ_TO 0x0000FFFFU
#define PHY_WRITE_TO 0x0000FFFFU

/* ------------------- Section 3: Common PHY Registers -------------------- */

// Transceiver Basic Control Register
#define PHY_BCR ((uint16_t) 0x0000)
// Transceiver Basic Status Register
#define PHY_BSR ((uint16_t) 0x0001)

// PHY Reset
#define PHY_RESET ((uint16_t) 0x8000)
// Select loop-back mode
#define PHY_LOOPBACK ((uint16_t) 0x4000)
// Set the full-duplex mode at 100 Mb/s
#define PHY_FULLDUPLEX_100M ((uint16_t) 0x2100)
// Set the half-duplex mode at 100 Mb/s
#define PHY_HALFDUPLEX_100M ((uint16_t) 0x2000)
// Set the full-duplex mode at 10 Mb/s
#define PHY_FULLDUPLEX_10M ((uint16_t) 0x0100)
// Set the half-duplex mode at 10 Mb/s
#define PHY_HALFDUPLEX_10M ((uint16_t) 0x0000)
// Enable auto-negotiation function
#define PHY_AUTONEGOTIATION ((uint16_t) 0x1000)
// Restart auto-negotiation function
#define PHY_RESTART_AUTONEGOTIATION ((uint16_t) 0x0200)
// Select the power down mode
#define PHY_POWERDOWN ((uint16_t) 0x0800)
// Isolate PHY from MII
#define PHY_ISOLATE ((uint16_t) 0x0400)

// Auto-Negotiation process completed
#define PHY_AUTONEGO_COMPLETE ((uint16_t) 0x0020)
// Valid link established
#define PHY_LINKED_STATUS ((uint16_t) 0x0004)
// Jabber condition detected
#define PHY_JABBER_DETECTION ((uint16_t) 0x0002)

/* ------------------ Section 4: Extended PHY Registers ------------------- */

// PHY status register Offset
#define PHY_SR ((uint16_t) 0x0010)
// MII Interrupt Control Register
#define PHY_MICR ((uint16_t) 0x0011)
// MII Interrupt Status and Misc. Control Register
#define PHY_MISR ((uint16_t) 0x0012)

// PHY Link mask
#define PHY_LINK_STATUS ((uint16_t) 0x0001)
// PHY Speed mask
#define PHY_SPEED_STATUS ((uint16_t) 0x0002)
// PHY Duplex mask
#define PHY_DUPLEX_STATUS ((uint16_t) 0x0004)

// PHY Enable interrupts
#define PHY_MICR_INT_EN ((uint16_t) 0x0002)
// PHY Enable output interrupt events
#define PHY_MICR_INT_OE ((uint16_t) 0x0001)

// Enable Interrupt on change of link status
#define PHY_MISR_LINK_INT_EN ((uint16_t) 0x0020)
// PHY link status interrupt mask
#define PHY_LINK_INTERRUPT ((uint16_t) 0x2000)

/* ================================================== HAL modules' configuration ================================================== */

// HAL Initialization module
#define HAL_MODULE_ENABLED

// HAL Core module
#define HAL_CORTEX_MODULE_ENABLED

// HAL Peripheral modules
// #define HAL_ADC_MODULE_ENABLED
// #define HAL_CAN_MODULE_ENABLED
// #define HAL_CAN_LEGACY_MODULE_ENABLED
// #define HAL_CEC_MODULE_ENABLED
// #define HAL_COMP_MODULE_ENABLED
// #define HAL_CORDIC_MODULE_ENABLED
// #define HAL_CRC_MODULE_ENABLED
// #define HAL_CRYP_MODULE_ENABLED
// #define HAL_DAC_MODULE_ENABLED
// #define HAL_DCMI_MODULE_ENABLED
// #define HAL_DFSDM_MODULE_ENABLED
// #define HAL_DMA2D_MODULE_ENABLED
// #define HAL_DMA_MODULE_ENABLED
// #define HAL_DSI_MODULE_ENABLED
// #define HAL_DTS_MODULE_ENABLED
// #define HAL_ETH_MODULE_ENABLED
// #define HAL_EXTI_MODULE_ENABLED
// #define HAL_FDCAN_MODULE_ENABLED
// #define HAL_FIREWALL_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
// #define HAL_FMAC_MODULE_ENABLED
// #define HAL_FMPI2C_MODULE_ENABLED
// #define HAL_FMPSMBUS_MODULE_ENABLED
// #define HAL_GFXMMU_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
// #define HAL_GTZC_MODULE_ENABLED
// #define HAL_HASH_MODULE_ENABLED
// #define HAL_HCD_MODULE_ENABLED
// #define HAL_HRTIM_MODULE_ENABLED
// #define HAL_HSEM_MODULE_ENABLED
// #define HAL_I2C_MODULE_ENABLED
// #define HAL_I2S_MODULE_ENABLED
// #define HAL_ICACHE_MODULE_ENABLED
// #define HAL_IRDA_MODULE_ENABLED
// #define HAL_IWDG_MODULE_ENABLED
// #define HAL_JPEG_MODULE_ENABLED
// #define HAL_LCD_MODULE_ENABLED
// #define HAL_LPTIM_MODULE_ENABLED
// #define HAL_LTDC_MODULE_ENABLED
// #define HAL_MDIOS_MODULE_ENABLED
// #define HAL_MDMA_MODULE_ENABLED
// #define HAL_MMC_MODULE_ENABLED
// #define HAL_NAND_MODULE_ENABLED
// #define HAL_NOR_MODULE_ENABLED
// #define HAL_OPAMP_MODULE_ENABLED
// #define HAL_OSPI_MODULE_ENABLED
// #define HAL_OTFDEC_MODULE_ENABLED
// #define HAL_PCCARD_MODULE_ENABLED
// #define HAL_PCD_MODULE_ENABLED
// #define HAL_PKA_MODULE_ENABLED
// #define HAL_PSSI_MODULE_ENABLED
// #define HAL_PWR_MODULE_ENABLED
// #define HAL_QSPI_MODULE_ENABLED
// #define HAL_RAMECC_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
// #define HAL_RNG_MODULE_ENABLED
// #define HAL_RTC_MODULE_ENABLED
// #define HAL_SAI_MODULE_ENABLED
// #define HAL_SDADC_MODULE_ENABLED
// #define HAL_SDRAM_MODULE_ENABLED
// #define HAL_SD_MODULE_ENABLED
// #define HAL_SMARTCARD_MODULE_ENABLED
// #define HAL_SMBUS_MODULE_ENABLED
// #define HAL_SPDIFRX_MODULE_ENABLED
// #define HAL_SPI_MODULE_ENABLED
// #define HAL_SRAM_MODULE_ENABLED
// #define HAL_SWPMI_MODULE_ENABLED
// #define HAL_TIM_MODULE_ENABLED
// #define HAL_TSC_MODULE_ENABLED
// #define HAL_UART_MODULE_ENABLED
// #define HAL_USART_MODULE_ENABLED
// #define HAL_WWDG_MODULE_ENABLED

/* =============================================== Module's callback configurations =============================================== */

#define  USE_HAL_ADC_REGISTER_CALLBACKS       0U
#define  USE_HAL_CAN_REGISTER_CALLBACKS       0U
#define  USE_HAL_CEC_REGISTER_CALLBACKS       0U
#define  USE_HAL_COMP_REGISTER_CALLBACKS      0U
#define  USE_HAL_CORDIC_REGISTER_CALLBACKS    0U
#define  USE_HAL_CRYP_REGISTER_CALLBACKS      0U
#define  USE_HAL_DAC_REGISTER_CALLBACKS       0U
#define  USE_HAL_DCMI_REGISTER_CALLBACKS      0U
#define  USE_HAL_DFSDM_REGISTER_CALLBACKS     0U
#define  USE_HAL_DMA2D_REGISTER_CALLBACKS     0U
#define  USE_HAL_DSI_REGISTER_CALLBACKS       0U
#define  USE_HAL_DTS_REGISTER_CALLBACKS       0U
#define  USE_HAL_ETH_REGISTER_CALLBACKS       0U
#define  USE_HAL_FDCAN_REGISTER_CALLBACKS     0U
#define  USE_HAL_FMAC_REGISTER_CALLBACKS      0U
#define  USE_HAL_FMPI2C_REGISTER_CALLBACKS    0U
#define  USE_HAL_FMPSMBUS_REGISTER_CALLBACKS  0U
#define  USE_HAL_GFXMMU_REGISTER_CALLBACKS    0U
#define  USE_HAL_HASH_REGISTER_CALLBACKS      0U
#define  USE_HAL_HCD_REGISTER_CALLBACKS       0U
#define  USE_HAL_HRTIM_REGISTER_CALLBACKS     0U
#define  USE_HAL_I2C_REGISTER_CALLBACKS       0U
#define  USE_HAL_I2S_REGISTER_CALLBACKS       0U
#define  USE_HAL_IRDA_REGISTER_CALLBACKS      0U
#define  USE_HAL_JPEG_REGISTER_CALLBACKS      0U
#define  USE_HAL_LPTIM_REGISTER_CALLBACKS     0U
#define  USE_HAL_LTDC_REGISTER_CALLBACKS      0U
#define  USE_HAL_MDIOS_REGISTER_CALLBACKS     0U
#define  USE_HAL_MMC_REGISTER_CALLBACKS       0U
#define  USE_HAL_NAND_REGISTER_CALLBACKS      0U
#define  USE_HAL_NOR_REGISTER_CALLBACKS       0U
#define  USE_HAL_OPAMP_REGISTER_CALLBACKS     0U
#define  USE_HAL_OSPI_REGISTER_CALLBACKS      0U
#define  USE_HAL_OTFDEC_REGISTER_CALLBACKS    0U
#define  USE_HAL_PCCARD_REGISTER_CALLBACKS    0U
#define  USE_HAL_PCD_REGISTER_CALLBACKS       0U
#define  USE_HAL_QSPI_REGISTER_CALLBACKS      0U
#define  USE_HAL_RNG_REGISTER_CALLBACKS       0U
#define  USE_HAL_RTC_REGISTER_CALLBACKS       0U
#define  USE_HAL_SAI_REGISTER_CALLBACKS       0U
#define  USE_HAL_SDADC_REGISTER_CALLBACKS     0U
#define  USE_HAL_SDRAM_REGISTER_CALLBACKS     0U
#define  USE_HAL_SD_REGISTER_CALLBACKS        0U
#define  USE_HAL_SMARTCARD_REGISTER_CALLBACKS 0U
#define  USE_HAL_SMBUS_REGISTER_CALLBACKS     0U
#define  USE_HAL_SPDIFRX_REGISTER_CALLBACKS   0U
#define  USE_HAL_SPI_REGISTER_CALLBACKS       0U
#define  USE_HAL_SRAM_REGISTER_CALLBACKS      0U
#define  USE_HAL_SWPMI_REGISTER_CALLBACKS     0U
#define  USE_HAL_TIM_REGISTER_CALLBACKS       0U
#define  USE_HAL_TSC_REGISTER_CALLBACKS       0U
#define  USE_HAL_UART_REGISTER_CALLBACKS      0U
#define  USE_HAL_USART_REGISTER_CALLBACKS     0U
#define  USE_HAL_WWDG_REGISTER_CALLBACKS      0U

/* =============================================== Additional modules' configuration ============================================== */

// Use CRC module to code SPI data (when appliccabble) [?]
#define USE_SPI_CRC 1U

// CRYP peripheral configuration
#define USE_HAL_CRYP_SUSPEND_RESUME 1U

// SD transereceiver usage
#define USE_SD_TRANSCEIVER 

/* =========================================================== Includes =========================================================== */

#include "hal_assert.h"

/* ================================================================================================================================ */

#endif
