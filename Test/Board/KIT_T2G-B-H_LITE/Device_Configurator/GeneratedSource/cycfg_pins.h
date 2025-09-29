/*******************************************************************************
 * File Name: cycfg_pins.h
 *
 * Description:
 * Pin configuration
 * This file was automatically generated and should not be modified.
 * Configurator Backend 3.60.0
 * device-db 4.21.0.7643
 * mtb-pdl-cat1 3.14.0.38372
 *
 *******************************************************************************
 * Copyright 2025 Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#if !defined(CYCFG_PINS_H)
#define CYCFG_PINS_H

#include "cycfg_notices.h"
#include "cy_gpio.h"
#include "cycfg_routing.h"

#if defined (CY_USING_HAL)
#include "cyhal_hwmgr.h"
#endif /* defined (CY_USING_HAL) */

#if defined (CY_USING_HAL_LITE)
#include "cyhal_hw_types.h"
#endif /* defined (CY_USING_HAL_LITE) */

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

#define CYBSP_DEBUG_UART_RX_ENABLED 1U
#define CYBSP_DEBUG_UART_RX_PORT GPIO_PRT0
#define CYBSP_DEBUG_UART_RX_PORT_NUM 0U
#define CYBSP_DEBUG_UART_RX_PIN 0U
#define CYBSP_DEBUG_UART_RX_NUM 0U
#define CYBSP_DEBUG_UART_RX_DRIVEMODE CY_GPIO_DM_HIGHZ
#define CYBSP_DEBUG_UART_RX_INIT_DRIVESTATE 1
#ifndef ioss_0_port_0_pin_0_HSIOM
    #define ioss_0_port_0_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_DEBUG_UART_RX_HSIOM ioss_0_port_0_pin_0_HSIOM
#define CYBSP_DEBUG_UART_RX_IRQ ioss_interrupts_gpio_dpslp_0_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_DEBUG_UART_RX_HAL_PORT_PIN P0_0
#define CYBSP_DEBUG_UART_RX P0_0
#define CYBSP_DEBUG_UART_RX_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_DEBUG_UART_RX_HAL_DIR CYHAL_GPIO_DIR_INPUT 
#define CYBSP_DEBUG_UART_RX_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_NONE
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_DEBUG_UART_TX_ENABLED 1U
#define CYBSP_DEBUG_UART_TX_PORT GPIO_PRT0
#define CYBSP_DEBUG_UART_TX_PORT_NUM 0U
#define CYBSP_DEBUG_UART_TX_PIN 1U
#define CYBSP_DEBUG_UART_TX_NUM 1U
#define CYBSP_DEBUG_UART_TX_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CYBSP_DEBUG_UART_TX_INIT_DRIVESTATE 1
#ifndef ioss_0_port_0_pin_1_HSIOM
    #define ioss_0_port_0_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_DEBUG_UART_TX_HSIOM ioss_0_port_0_pin_1_HSIOM
#define CYBSP_DEBUG_UART_TX_IRQ ioss_interrupts_gpio_dpslp_0_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_DEBUG_UART_TX_HAL_PORT_PIN P0_1
#define CYBSP_DEBUG_UART_TX P0_1
#define CYBSP_DEBUG_UART_TX_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_DEBUG_UART_TX_HAL_DIR CYHAL_GPIO_DIR_OUTPUT 
#define CYBSP_DEBUG_UART_TX_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_STRONG
#define CYBSP_D2 (P0_2)
#define CYBSP_S2G_0_INT CYBSP_D2
#define CYBSP_D3 (P0_3)
#define CYBSP_S2G_0_PWM CYBSP_D3
#define CYBSP_D9 (P11_0)
#define CYBSP_S2G_0_RST CYBSP_D9
#define CYBSP_S2G_1_RST (P11_1)
#define CYBSP_MIKROBUS_RST (P11_2)
#define CYBSP_CAN_TX (P12_0)
#define CYBSP_CAN_RX (P12_1)
#define CYBSP_A1 (P12_2)
#define CYBSP_S2G_0_AN1 CYBSP_A1
#define CYBSP_A2 (P12_3)
#define CYBSP_S2G_0_AN2 CYBSP_A2
#define CYBSP_A3 (P12_4)
#define CYBSP_S2G_1_AN1 CYBSP_A3
#define CYBSP_SPI_MISO (P13_0)
#define CYBSP_D12 CYBSP_SPI_MISO
#define CYBSP_MIKROBUS_SPI_MISO CYBSP_SPI_MISO
#define CYBSP_S2G_0_SPI_MISO CYBSP_SPI_MISO
#define CYBSP_S2G_1_SPI_MISO CYBSP_SPI_MISO
#define CYBSP_SPI_MOSI (P13_1)
#define CYBSP_D11 CYBSP_SPI_MOSI
#define CYBSP_MIKROBUS_SPI_MOSI CYBSP_SPI_MOSI
#define CYBSP_S2G_0_SPI_MOSI CYBSP_SPI_MOSI
#define CYBSP_S2G_1_SPI_MOSI CYBSP_SPI_MOSI
#define CYBSP_SPI_CLK (P13_2)
#define CYBSP_D13 CYBSP_SPI_CLK
#define CYBSP_MIKROBUS_SPI_SCK CYBSP_SPI_CLK
#define CYBSP_S2G_0_SPI_SCLK CYBSP_SPI_CLK
#define CYBSP_S2G_1_SPI_SCLK CYBSP_SPI_CLK
#define CYBSP_S2G_0_SPI_CS (P13_3)
#define CYBSP_S2G_1_SPI_CS (P13_4)
#define CYBSP_MIKROBUS_SPI_CS (P13_5)
#define CYBSP_SPI_CS (P13_6)
#define CYBSP_D10 CYBSP_SPI_CS
#define CYBSP_A4 (P13_7)
#define CYBSP_S2G_1_AN2 CYBSP_A4
#define CYBSP_D0 (P14_0)
#define CYBSP_MIKROBUS_UART_RX CYBSP_D0
#define CYBSP_S2G_0_UART_RX CYBSP_D0
#define CYBSP_S2G_1_UART_RX CYBSP_D0
#define CYBSP_D1 (P14_1)
#define CYBSP_MIKROBUS_UART_TX CYBSP_D1
#define CYBSP_S2G_0_UART_TX CYBSP_D1
#define CYBSP_S2G_1_UART_TX CYBSP_D1
#define CYBSP_A5 (P14_2)
#define CYBSP_MIKROBUS_AN CYBSP_A5
#define CYBSP_D6 (P14_3)
#define CYBSP_MIKROBUS_PWM CYBSP_D6
#define C (P14_7)
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_USER_BTN2_ENABLED 1U
#define CYBSP_USER_BTN2_PORT GPIO_PRT17
#define CYBSP_USER_BTN2_PORT_NUM 17U
#define CYBSP_USER_BTN2_PIN 0U
#define CYBSP_USER_BTN2_NUM 0U
#define CYBSP_USER_BTN2_DRIVEMODE CY_GPIO_DM_PULLUP
#define CYBSP_USER_BTN2_INIT_DRIVESTATE 1
#ifndef ioss_0_port_17_pin_0_HSIOM
    #define ioss_0_port_17_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_USER_BTN2_HSIOM ioss_0_port_17_pin_0_HSIOM
#define CYBSP_USER_BTN2_IRQ ioss_interrupts_gpio_dpslp_17_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_USER_BTN2_HAL_PORT_PIN P17_0
#define CYBSP_USER_BTN2 P17_0
#define CYBSP_USER_BTN2_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_USER_BTN2_HAL_DIR CYHAL_GPIO_DIR_BIDIRECTIONAL 
#define CYBSP_USER_BTN2_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_PULLUP
#define CYBSP_D7 (P17_1)
#define CYBSP_S2G_0_GPIO1 CYBSP_D7
#define CYBSP_D8 (P17_2)
#define CYBSP_MIKROBUS_INT CYBSP_D8
#define CYBSP_S2G_1_GPIO1 CYBSP_D8
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_ETH_REF_CLK_ENABLED 1U
#define CYBSP_ETH_REF_CLK_PORT GPIO_PRT18
#define CYBSP_ETH_REF_CLK_PORT_NUM 18U
#define CYBSP_ETH_REF_CLK_PIN 0U
#define CYBSP_ETH_REF_CLK_NUM 0U
#define CYBSP_ETH_REF_CLK_DRIVEMODE CY_GPIO_DM_HIGHZ
#define CYBSP_ETH_REF_CLK_INIT_DRIVESTATE 0
#ifndef ioss_0_port_18_pin_0_HSIOM
    #define ioss_0_port_18_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_ETH_REF_CLK_HSIOM ioss_0_port_18_pin_0_HSIOM
#define CYBSP_ETH_REF_CLK_IRQ ioss_interrupts_gpio_dpslp_18_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_ETH_REF_CLK_HAL_PORT_PIN P18_0
#define CYBSP_ETH_REF_CLK P18_0
#define CYBSP_ETH_REF_CLK_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_ETH_REF_CLK_HAL_DIR CYHAL_GPIO_DIR_INPUT 
#define CYBSP_ETH_REF_CLK_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_NONE
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_ETH_TX_CTL_ENABLED 1U
#define CYBSP_ETH_TX_CTL_PORT GPIO_PRT18
#define CYBSP_ETH_TX_CTL_PORT_NUM 18U
#define CYBSP_ETH_TX_CTL_PIN 1U
#define CYBSP_ETH_TX_CTL_NUM 1U
#define CYBSP_ETH_TX_CTL_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CYBSP_ETH_TX_CTL_INIT_DRIVESTATE 0
#ifndef ioss_0_port_18_pin_1_HSIOM
    #define ioss_0_port_18_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_ETH_TX_CTL_HSIOM ioss_0_port_18_pin_1_HSIOM
#define CYBSP_ETH_TX_CTL_IRQ ioss_interrupts_gpio_dpslp_18_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_ETH_TX_CTL_HAL_PORT_PIN P18_1
#define CYBSP_ETH_TX_CTL P18_1
#define CYBSP_ETH_TX_CTL_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_ETH_TX_CTL_HAL_DIR CYHAL_GPIO_DIR_OUTPUT 
#define CYBSP_ETH_TX_CTL_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_STRONG
#define CYBSP_ETH_TX_GTXCLK (P18_3)
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_ETH_TXD_0_ENABLED 1U
#define CYBSP_ETH_TXD_0_PORT GPIO_PRT18
#define CYBSP_ETH_TXD_0_PORT_NUM 18U
#define CYBSP_ETH_TXD_0_PIN 4U
#define CYBSP_ETH_TXD_0_NUM 4U
#define CYBSP_ETH_TXD_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CYBSP_ETH_TXD_0_INIT_DRIVESTATE 0
#ifndef ioss_0_port_18_pin_4_HSIOM
    #define ioss_0_port_18_pin_4_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_ETH_TXD_0_HSIOM ioss_0_port_18_pin_4_HSIOM
#define CYBSP_ETH_TXD_0_IRQ ioss_interrupts_gpio_dpslp_18_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_ETH_TXD_0_HAL_PORT_PIN P18_4
#define CYBSP_ETH_TXD_0 P18_4
#define CYBSP_ETH_TXD_0_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_ETH_TXD_0_HAL_DIR CYHAL_GPIO_DIR_OUTPUT 
#define CYBSP_ETH_TXD_0_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_STRONG
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_ETH_TXD_1_ENABLED 1U
#define CYBSP_ETH_TXD_1_PORT GPIO_PRT18
#define CYBSP_ETH_TXD_1_PORT_NUM 18U
#define CYBSP_ETH_TXD_1_PIN 5U
#define CYBSP_ETH_TXD_1_NUM 5U
#define CYBSP_ETH_TXD_1_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CYBSP_ETH_TXD_1_INIT_DRIVESTATE 0
#ifndef ioss_0_port_18_pin_5_HSIOM
    #define ioss_0_port_18_pin_5_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_ETH_TXD_1_HSIOM ioss_0_port_18_pin_5_HSIOM
#define CYBSP_ETH_TXD_1_IRQ ioss_interrupts_gpio_dpslp_18_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_ETH_TXD_1_HAL_PORT_PIN P18_5
#define CYBSP_ETH_TXD_1 P18_5
#define CYBSP_ETH_TXD_1_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_ETH_TXD_1_HAL_DIR CYHAL_GPIO_DIR_OUTPUT 
#define CYBSP_ETH_TXD_1_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_STRONG
#define CYBSP_ETH_TXD_2 (P18_6)
#define CYBSP_ETH_TXD_3 (P18_7)
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_ETH_RXD0_ENABLED 1U
#define CYBSP_ETH_RXD0_PORT GPIO_PRT19
#define CYBSP_ETH_RXD0_PORT_NUM 19U
#define CYBSP_ETH_RXD0_PIN 0U
#define CYBSP_ETH_RXD0_NUM 0U
#define CYBSP_ETH_RXD0_DRIVEMODE CY_GPIO_DM_HIGHZ
#define CYBSP_ETH_RXD0_INIT_DRIVESTATE 0
#ifndef ioss_0_port_19_pin_0_HSIOM
    #define ioss_0_port_19_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_ETH_RXD0_HSIOM ioss_0_port_19_pin_0_HSIOM
#define CYBSP_ETH_RXD0_IRQ ioss_interrupts_gpio_dpslp_19_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_ETH_RXD0_HAL_PORT_PIN P19_0
#define CYBSP_ETH_RXD0 P19_0
#define CYBSP_ETH_RXD0_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_ETH_RXD0_HAL_DIR CYHAL_GPIO_DIR_INPUT 
#define CYBSP_ETH_RXD0_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_NONE
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_ETH_RXD1_ENABLED 1U
#define CYBSP_ETH_RXD1_PORT GPIO_PRT19
#define CYBSP_ETH_RXD1_PORT_NUM 19U
#define CYBSP_ETH_RXD1_PIN 1U
#define CYBSP_ETH_RXD1_NUM 1U
#define CYBSP_ETH_RXD1_DRIVEMODE CY_GPIO_DM_HIGHZ
#define CYBSP_ETH_RXD1_INIT_DRIVESTATE 0
#ifndef ioss_0_port_19_pin_1_HSIOM
    #define ioss_0_port_19_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_ETH_RXD1_HSIOM ioss_0_port_19_pin_1_HSIOM
#define CYBSP_ETH_RXD1_IRQ ioss_interrupts_gpio_dpslp_19_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_ETH_RXD1_HAL_PORT_PIN P19_1
#define CYBSP_ETH_RXD1 P19_1
#define CYBSP_ETH_RXD1_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_ETH_RXD1_HAL_DIR CYHAL_GPIO_DIR_INPUT 
#define CYBSP_ETH_RXD1_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_NONE
#define CYBSP_ETH_RXD_0 (P20_0)
#define CYBSP_ETH_RXD_1 (P20_1)
#define CYBSP_ETH_RXD_2 (P20_2)
#define CYBSP_ETH_RXD_3 (P20_3)
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_WCO_IN_ENABLED 1U
#define CYBSP_WCO_IN_PORT GPIO_PRT21
#define CYBSP_WCO_IN_PORT_NUM 21U
#define CYBSP_WCO_IN_PIN 0U
#define CYBSP_WCO_IN_NUM 0U
#define CYBSP_WCO_IN_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_WCO_IN_INIT_DRIVESTATE 1
#ifndef ioss_0_port_21_pin_0_HSIOM
    #define ioss_0_port_21_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_WCO_IN_HSIOM ioss_0_port_21_pin_0_HSIOM
#define CYBSP_WCO_IN_IRQ ioss_interrupts_gpio_dpslp_21_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_WCO_IN_HAL_PORT_PIN P21_0
#define CYBSP_WCO_IN P21_0
#define CYBSP_WCO_IN_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_WCO_IN_HAL_DIR CYHAL_GPIO_DIR_INPUT 
#define CYBSP_WCO_IN_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_WCO_OUT_ENABLED 1U
#define CYBSP_WCO_OUT_PORT GPIO_PRT21
#define CYBSP_WCO_OUT_PORT_NUM 21U
#define CYBSP_WCO_OUT_PIN 1U
#define CYBSP_WCO_OUT_NUM 1U
#define CYBSP_WCO_OUT_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_WCO_OUT_INIT_DRIVESTATE 1
#ifndef ioss_0_port_21_pin_1_HSIOM
    #define ioss_0_port_21_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_WCO_OUT_HSIOM ioss_0_port_21_pin_1_HSIOM
#define CYBSP_WCO_OUT_IRQ ioss_interrupts_gpio_dpslp_21_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_WCO_OUT_HAL_PORT_PIN P21_1
#define CYBSP_WCO_OUT P21_1
#define CYBSP_WCO_OUT_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_WCO_OUT_HAL_DIR CYHAL_GPIO_DIR_INPUT 
#define CYBSP_WCO_OUT_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_ECO_IN_ENABLED 1U
#define CYBSP_ECO_IN_PORT GPIO_PRT21
#define CYBSP_ECO_IN_PORT_NUM 21U
#define CYBSP_ECO_IN_PIN 2U
#define CYBSP_ECO_IN_NUM 2U
#define CYBSP_ECO_IN_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_ECO_IN_INIT_DRIVESTATE 1
#ifndef ioss_0_port_21_pin_2_HSIOM
    #define ioss_0_port_21_pin_2_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_ECO_IN_HSIOM ioss_0_port_21_pin_2_HSIOM
#define CYBSP_ECO_IN_IRQ ioss_interrupts_gpio_dpslp_21_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_ECO_IN_HAL_PORT_PIN P21_2
#define CYBSP_ECO_IN P21_2
#define CYBSP_ECO_IN_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_ECO_IN_HAL_DIR CYHAL_GPIO_DIR_INPUT 
#define CYBSP_ECO_IN_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_ECO_OUT_ENABLED 1U
#define CYBSP_ECO_OUT_PORT GPIO_PRT21
#define CYBSP_ECO_OUT_PORT_NUM 21U
#define CYBSP_ECO_OUT_PIN 3U
#define CYBSP_ECO_OUT_NUM 3U
#define CYBSP_ECO_OUT_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_ECO_OUT_INIT_DRIVESTATE 1
#ifndef ioss_0_port_21_pin_3_HSIOM
    #define ioss_0_port_21_pin_3_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_ECO_OUT_HSIOM ioss_0_port_21_pin_3_HSIOM
#define CYBSP_ECO_OUT_IRQ ioss_interrupts_gpio_dpslp_21_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_ECO_OUT_HAL_PORT_PIN P21_3
#define CYBSP_ECO_OUT P21_3
#define CYBSP_ECO_OUT_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_ECO_OUT_HAL_DIR CYHAL_GPIO_DIR_INPUT 
#define CYBSP_ECO_OUT_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_ETH_RX_CTL_ENABLED 1U
#define CYBSP_ETH_RX_CTL_PORT GPIO_PRT21
#define CYBSP_ETH_RX_CTL_PORT_NUM 21U
#define CYBSP_ETH_RX_CTL_PIN 5U
#define CYBSP_ETH_RX_CTL_NUM 5U
#define CYBSP_ETH_RX_CTL_DRIVEMODE CY_GPIO_DM_HIGHZ
#define CYBSP_ETH_RX_CTL_INIT_DRIVESTATE 0
#ifndef ioss_0_port_21_pin_5_HSIOM
    #define ioss_0_port_21_pin_5_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_ETH_RX_CTL_HSIOM ioss_0_port_21_pin_5_HSIOM
#define CYBSP_ETH_RX_CTL_IRQ ioss_interrupts_gpio_dpslp_21_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_ETH_RX_CTL_HAL_PORT_PIN P21_5
#define CYBSP_ETH_RX_CTL P21_5
#define CYBSP_ETH_RX_CTL_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_ETH_RX_CTL_HAL_DIR CYHAL_GPIO_DIR_INPUT 
#define CYBSP_ETH_RX_CTL_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_NONE
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_SWO_ENABLED 1U
#define CYBSP_SWO_PORT GPIO_PRT23
#define CYBSP_SWO_PORT_NUM 23U
#define CYBSP_SWO_PIN 4U
#define CYBSP_SWO_NUM 4U
#define CYBSP_SWO_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CYBSP_SWO_INIT_DRIVESTATE 1
#ifndef ioss_0_port_23_pin_4_HSIOM
    #define ioss_0_port_23_pin_4_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_SWO_HSIOM ioss_0_port_23_pin_4_HSIOM
#define CYBSP_SWO_IRQ ioss_interrupts_gpio_dpslp_23_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_SWO_HAL_PORT_PIN P23_4
#define CYBSP_SWO P23_4
#define CYBSP_SWO_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_SWO_HAL_DIR CYHAL_GPIO_DIR_OUTPUT 
#define CYBSP_SWO_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_STRONG
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_SWDCK_ENABLED 1U
#define CYBSP_SWDCK_PORT GPIO_PRT23
#define CYBSP_SWDCK_PORT_NUM 23U
#define CYBSP_SWDCK_PIN 5U
#define CYBSP_SWDCK_NUM 5U
#define CYBSP_SWDCK_DRIVEMODE CY_GPIO_DM_PULLDOWN
#define CYBSP_SWDCK_INIT_DRIVESTATE 1
#ifndef ioss_0_port_23_pin_5_HSIOM
    #define ioss_0_port_23_pin_5_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_SWDCK_HSIOM ioss_0_port_23_pin_5_HSIOM
#define CYBSP_SWDCK_IRQ ioss_interrupts_gpio_dpslp_23_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_SWDCK_HAL_PORT_PIN P23_5
#define CYBSP_SWDCK P23_5
#define CYBSP_SWDCK_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_SWDCK_HAL_DIR CYHAL_GPIO_DIR_BIDIRECTIONAL 
#define CYBSP_SWDCK_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_PULLDOWN
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_SWDIO_ENABLED 1U
#define CYBSP_SWDIO_PORT GPIO_PRT23
#define CYBSP_SWDIO_PORT_NUM 23U
#define CYBSP_SWDIO_PIN 6U
#define CYBSP_SWDIO_NUM 6U
#define CYBSP_SWDIO_DRIVEMODE CY_GPIO_DM_PULLUP
#define CYBSP_SWDIO_INIT_DRIVESTATE 1
#ifndef ioss_0_port_23_pin_6_HSIOM
    #define ioss_0_port_23_pin_6_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_SWDIO_HSIOM ioss_0_port_23_pin_6_HSIOM
#define CYBSP_SWDIO_IRQ ioss_interrupts_gpio_dpslp_23_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_SWDIO_HAL_PORT_PIN P23_6
#define CYBSP_SWDIO P23_6
#define CYBSP_SWDIO_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_SWDIO_HAL_DIR CYHAL_GPIO_DIR_BIDIRECTIONAL 
#define CYBSP_SWDIO_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_PULLUP
#define CYBSP_D4 (P2_0)
#define CYBSP_S2G_1_INT CYBSP_D4
#define CYBSP_D5 (P2_1)
#define CYBSP_S2G_1_PWM CYBSP_D5
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_ETH_MDIO_ENABLED 1U
#define CYBSP_ETH_MDIO_PORT GPIO_PRT3
#define CYBSP_ETH_MDIO_PORT_NUM 3U
#define CYBSP_ETH_MDIO_PIN 0U
#define CYBSP_ETH_MDIO_NUM 0U
#define CYBSP_ETH_MDIO_DRIVEMODE CY_GPIO_DM_STRONG
#define CYBSP_ETH_MDIO_INIT_DRIVESTATE 0
#ifndef ioss_0_port_3_pin_0_HSIOM
    #define ioss_0_port_3_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_ETH_MDIO_HSIOM ioss_0_port_3_pin_0_HSIOM
#define CYBSP_ETH_MDIO_IRQ ioss_interrupts_gpio_dpslp_3_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_ETH_MDIO_HAL_PORT_PIN P3_0
#define CYBSP_ETH_MDIO P3_0
#define CYBSP_ETH_MDIO_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_ETH_MDIO_HAL_DIR CYHAL_GPIO_DIR_BIDIRECTIONAL 
#define CYBSP_ETH_MDIO_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_STRONG
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_ETH_MDC_ENABLED 1U
#define CYBSP_ETH_MDC_PORT GPIO_PRT3
#define CYBSP_ETH_MDC_PORT_NUM 3U
#define CYBSP_ETH_MDC_PIN 1U
#define CYBSP_ETH_MDC_NUM 1U
#define CYBSP_ETH_MDC_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CYBSP_ETH_MDC_INIT_DRIVESTATE 1
#ifndef ioss_0_port_3_pin_1_HSIOM
    #define ioss_0_port_3_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_ETH_MDC_HSIOM ioss_0_port_3_pin_1_HSIOM
#define CYBSP_ETH_MDC_IRQ ioss_interrupts_gpio_dpslp_3_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_ETH_MDC_HAL_PORT_PIN P3_1
#define CYBSP_ETH_MDC P3_1
#define CYBSP_ETH_MDC_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_ETH_MDC_HAL_DIR CYHAL_GPIO_DIR_OUTPUT 
#define CYBSP_ETH_MDC_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_STRONG
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_USER_LED_ENABLED 1U
#define CYBSP_USER_LED1_ENABLED CYBSP_USER_LED_ENABLED
#define LED1_ENABLED CYBSP_USER_LED_ENABLED
#define CYBSP_USER_LED_PORT GPIO_PRT5
#define CYBSP_USER_LED1_PORT CYBSP_USER_LED_PORT
#define LED1_PORT CYBSP_USER_LED_PORT
#define CYBSP_USER_LED_PORT_NUM 5U
#define CYBSP_USER_LED1_PORT_NUM CYBSP_USER_LED_PORT_NUM
#define LED1_PORT_NUM CYBSP_USER_LED_PORT_NUM
#define CYBSP_USER_LED_PIN 0U
#define CYBSP_USER_LED1_PIN CYBSP_USER_LED_PIN
#define LED1_PIN CYBSP_USER_LED_PIN
#define CYBSP_USER_LED_NUM 0U
#define CYBSP_USER_LED1_NUM CYBSP_USER_LED_NUM
#define LED1_NUM CYBSP_USER_LED_NUM
#define CYBSP_USER_LED_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CYBSP_USER_LED1_DRIVEMODE CYBSP_USER_LED_DRIVEMODE
#define LED1_DRIVEMODE CYBSP_USER_LED_DRIVEMODE
#define CYBSP_USER_LED_INIT_DRIVESTATE 1
#define CYBSP_USER_LED1_INIT_DRIVESTATE CYBSP_USER_LED_INIT_DRIVESTATE
#define LED1_INIT_DRIVESTATE CYBSP_USER_LED_INIT_DRIVESTATE
#ifndef ioss_0_port_5_pin_0_HSIOM
    #define ioss_0_port_5_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_USER_LED_HSIOM ioss_0_port_5_pin_0_HSIOM
#define CYBSP_USER_LED1_HSIOM CYBSP_USER_LED_HSIOM
#define LED1_HSIOM CYBSP_USER_LED_HSIOM
#define CYBSP_USER_LED_IRQ ioss_interrupts_gpio_dpslp_5_IRQn
#define CYBSP_USER_LED1_IRQ CYBSP_USER_LED_IRQ
#define LED1_IRQ CYBSP_USER_LED_IRQ

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_USER_LED_HAL_PORT_PIN P5_0
#define CYBSP_USER_LED1_HAL_PORT_PIN CYBSP_USER_LED_HAL_PORT_PIN
#define LED1_HAL_PORT_PIN CYBSP_USER_LED_HAL_PORT_PIN
#define CYBSP_USER_LED P5_0
#define CYBSP_USER_LED1 CYBSP_USER_LED
#define LED1 CYBSP_USER_LED
#define CYBSP_USER_LED_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_USER_LED1_HAL_IRQ CYBSP_USER_LED_HAL_IRQ
#define LED1_HAL_IRQ CYBSP_USER_LED_HAL_IRQ
#define CYBSP_USER_LED_HAL_DIR CYHAL_GPIO_DIR_OUTPUT 
#define CYBSP_USER_LED1_HAL_DIR CYBSP_USER_LED_HAL_DIR
#define LED1_HAL_DIR CYBSP_USER_LED_HAL_DIR
#define CYBSP_USER_LED_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_STRONG
#define CYBSP_USER_LED1_HAL_DRIVEMODE CYBSP_USER_LED_HAL_DRIVEMODE
#define LED1_HAL_DRIVEMODE CYBSP_USER_LED_HAL_DRIVEMODE
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_USER_LED2_ENABLED 1U
#define LED2_ENABLED CYBSP_USER_LED2_ENABLED
#define CYBSP_USER_LED2_PORT GPIO_PRT5
#define LED2_PORT CYBSP_USER_LED2_PORT
#define CYBSP_USER_LED2_PORT_NUM 5U
#define LED2_PORT_NUM CYBSP_USER_LED2_PORT_NUM
#define CYBSP_USER_LED2_PIN 1U
#define LED2_PIN CYBSP_USER_LED2_PIN
#define CYBSP_USER_LED2_NUM 1U
#define LED2_NUM CYBSP_USER_LED2_NUM
#define CYBSP_USER_LED2_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define LED2_DRIVEMODE CYBSP_USER_LED2_DRIVEMODE
#define CYBSP_USER_LED2_INIT_DRIVESTATE 1
#define LED2_INIT_DRIVESTATE CYBSP_USER_LED2_INIT_DRIVESTATE
#ifndef ioss_0_port_5_pin_1_HSIOM
    #define ioss_0_port_5_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_USER_LED2_HSIOM ioss_0_port_5_pin_1_HSIOM
#define LED2_HSIOM CYBSP_USER_LED2_HSIOM
#define CYBSP_USER_LED2_IRQ ioss_interrupts_gpio_dpslp_5_IRQn
#define LED2_IRQ CYBSP_USER_LED2_IRQ

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_USER_LED2_HAL_PORT_PIN P5_1
#define LED2_HAL_PORT_PIN CYBSP_USER_LED2_HAL_PORT_PIN
#define CYBSP_USER_LED2 P5_1
#define LED2 CYBSP_USER_LED2
#define CYBSP_USER_LED2_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define LED2_HAL_IRQ CYBSP_USER_LED2_HAL_IRQ
#define CYBSP_USER_LED2_HAL_DIR CYHAL_GPIO_DIR_OUTPUT 
#define LED2_HAL_DIR CYBSP_USER_LED2_HAL_DIR
#define CYBSP_USER_LED2_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_STRONG
#define LED2_HAL_DRIVEMODE CYBSP_USER_LED2_HAL_DRIVEMODE
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_USER_LED3_ENABLED 1U
#define LED3_ENABLED CYBSP_USER_LED3_ENABLED
#define CYBSP_USER_LED3_PORT GPIO_PRT5
#define LED3_PORT CYBSP_USER_LED3_PORT
#define CYBSP_USER_LED3_PORT_NUM 5U
#define LED3_PORT_NUM CYBSP_USER_LED3_PORT_NUM
#define CYBSP_USER_LED3_PIN 2U
#define LED3_PIN CYBSP_USER_LED3_PIN
#define CYBSP_USER_LED3_NUM 2U
#define LED3_NUM CYBSP_USER_LED3_NUM
#define CYBSP_USER_LED3_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define LED3_DRIVEMODE CYBSP_USER_LED3_DRIVEMODE
#define CYBSP_USER_LED3_INIT_DRIVESTATE 1
#define LED3_INIT_DRIVESTATE CYBSP_USER_LED3_INIT_DRIVESTATE
#ifndef ioss_0_port_5_pin_2_HSIOM
    #define ioss_0_port_5_pin_2_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_USER_LED3_HSIOM ioss_0_port_5_pin_2_HSIOM
#define LED3_HSIOM CYBSP_USER_LED3_HSIOM
#define CYBSP_USER_LED3_IRQ ioss_interrupts_gpio_dpslp_5_IRQn
#define LED3_IRQ CYBSP_USER_LED3_IRQ

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_USER_LED3_HAL_PORT_PIN P5_2
#define LED3_HAL_PORT_PIN CYBSP_USER_LED3_HAL_PORT_PIN
#define CYBSP_USER_LED3 P5_2
#define LED3 CYBSP_USER_LED3
#define CYBSP_USER_LED3_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define LED3_HAL_IRQ CYBSP_USER_LED3_HAL_IRQ
#define CYBSP_USER_LED3_HAL_DIR CYHAL_GPIO_DIR_OUTPUT 
#define LED3_HAL_DIR CYBSP_USER_LED3_HAL_DIR
#define CYBSP_USER_LED3_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_STRONG
#define LED3_HAL_DRIVEMODE CYBSP_USER_LED3_HAL_DRIVEMODE
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_USER_BTN1_ENABLED 1U
#define CYBSP_USER_BTN_ENABLED CYBSP_USER_BTN1_ENABLED
#define CYBSP_USER_BTN1_PORT GPIO_PRT5
#define CYBSP_USER_BTN_PORT CYBSP_USER_BTN1_PORT
#define CYBSP_USER_BTN1_PORT_NUM 5U
#define CYBSP_USER_BTN_PORT_NUM CYBSP_USER_BTN1_PORT_NUM
#define CYBSP_USER_BTN1_PIN 3U
#define CYBSP_USER_BTN_PIN CYBSP_USER_BTN1_PIN
#define CYBSP_USER_BTN1_NUM 3U
#define CYBSP_USER_BTN_NUM CYBSP_USER_BTN1_NUM
#define CYBSP_USER_BTN1_DRIVEMODE CY_GPIO_DM_PULLUP
#define CYBSP_USER_BTN_DRIVEMODE CYBSP_USER_BTN1_DRIVEMODE
#define CYBSP_USER_BTN1_INIT_DRIVESTATE 1
#define CYBSP_USER_BTN_INIT_DRIVESTATE CYBSP_USER_BTN1_INIT_DRIVESTATE
#ifndef ioss_0_port_5_pin_3_HSIOM
    #define ioss_0_port_5_pin_3_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_USER_BTN1_HSIOM ioss_0_port_5_pin_3_HSIOM
#define CYBSP_USER_BTN_HSIOM CYBSP_USER_BTN1_HSIOM
#define CYBSP_USER_BTN1_IRQ ioss_interrupts_gpio_dpslp_5_IRQn
#define CYBSP_USER_BTN_IRQ CYBSP_USER_BTN1_IRQ

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_USER_BTN1_HAL_PORT_PIN P5_3
#define CYBSP_USER_BTN_HAL_PORT_PIN CYBSP_USER_BTN1_HAL_PORT_PIN
#define CYBSP_USER_BTN1 P5_3
#define CYBSP_USER_BTN CYBSP_USER_BTN1
#define CYBSP_USER_BTN1_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_USER_BTN_HAL_IRQ CYBSP_USER_BTN1_HAL_IRQ
#define CYBSP_USER_BTN1_HAL_DIR CYHAL_GPIO_DIR_BIDIRECTIONAL 
#define CYBSP_USER_BTN_HAL_DIR CYBSP_USER_BTN1_HAL_DIR
#define CYBSP_USER_BTN1_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_PULLUP
#define CYBSP_USER_BTN_HAL_DRIVEMODE CYBSP_USER_BTN1_HAL_DRIVEMODE
#define CYBSP_POT (P6_0)
#define CYBSP_A0 CYBSP_POT
#define CYBSP_I2C_SDA (P6_1)
#define CYBSP_MIKROBUS_I2C_SDA CYBSP_I2C_SDA
#define CYBSP_S2G_0_I2C_SDA CYBSP_I2C_SDA
#define CYBSP_S2G_1_I2C_SDA CYBSP_I2C_SDA
#define CYBSP_I2C_SCL (P6_2)
#define CYBSP_MIKROBUS_I2C_SCL CYBSP_I2C_SCL
#define CYBSP_S2G_0_I2C_SCL CYBSP_I2C_SCL
#define CYBSP_S2G_1_I2C_SCL CYBSP_I2C_SCL
#define CYBSP_QSPI_SCK (P6_3)
#define CYBSP_QSPI_SS (P6_5)
#define CYBSP_QSPI_FLASH_SSEL0 CYBSP_QSPI_SS
#define CYBSP_QSPI_FLASH_SSEL1 (P7_0)
#define CYBSP_QSPI_D0 (P7_1)
#define CYBSP_QSPI_D1 (P7_2)
#define CYBSP_QSPI_D2 (P7_3)
#define CYBSP_QSPI_D3 (P7_4)
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_DEBUG_UART_RX_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_DEBUG_UART_RX_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_DEBUG_UART_TX_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_DEBUG_UART_TX_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_USER_BTN2_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_USER_BTN2_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_ETH_REF_CLK_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_ETH_REF_CLK_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_ETH_TX_CTL_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_ETH_TX_CTL_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_ETH_TXD_0_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_ETH_TXD_0_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_ETH_TXD_1_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_ETH_TXD_1_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_ETH_RXD0_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_ETH_RXD0_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_ETH_RXD1_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_ETH_RXD1_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_WCO_IN_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_WCO_IN_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_WCO_OUT_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_WCO_OUT_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_ECO_IN_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_ECO_IN_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_ECO_OUT_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_ECO_OUT_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_ETH_RX_CTL_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_ETH_RX_CTL_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_SWO_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_SWO_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_SWDCK_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_SWDCK_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_SWDIO_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_SWDIO_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_ETH_MDIO_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_ETH_MDIO_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_ETH_MDC_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_ETH_MDC_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_USER_LED_config;

#define CYBSP_USER_LED1_config CYBSP_USER_LED_config
#define LED1_config CYBSP_USER_LED_config

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_USER_LED_obj;
#define CYBSP_USER_LED1_obj CYBSP_USER_LED_obj
#define LED1_obj CYBSP_USER_LED_obj
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_USER_LED2_config;

#define LED2_config CYBSP_USER_LED2_config

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_USER_LED2_obj;
#define LED2_obj CYBSP_USER_LED2_obj
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_USER_LED3_config;

#define LED3_config CYBSP_USER_LED3_config

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_USER_LED3_obj;
#define LED3_obj CYBSP_USER_LED3_obj
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_USER_BTN1_config;

#define CYBSP_USER_BTN_config CYBSP_USER_BTN1_config

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_USER_BTN1_obj;
#define CYBSP_USER_BTN_obj CYBSP_USER_BTN1_obj
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

void init_cycfg_pins(void);
void reserve_cycfg_pins(void);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* CYCFG_PINS_H */
