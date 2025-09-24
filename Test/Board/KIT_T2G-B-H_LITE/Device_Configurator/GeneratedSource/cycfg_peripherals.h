/*******************************************************************************
 * File Name: cycfg_peripherals.h
 *
 * Description:
 * Peripheral Hardware Block configuration
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

#if !defined(CYCFG_PERIPHERALS_H)
#define CYCFG_PERIPHERALS_H

#include "cycfg_notices.h"
#include "cy_scb_uart.h"
#include "cy_sysclk.h"

#if defined (CY_USING_HAL)
#include "cyhal_hwmgr.h"
#include "cyhal.h"
#endif /* defined (CY_USING_HAL) */

#if defined (COMPONENT_MTB_HAL)
#include "mtb_hal.h"
#include "cycfg_clocks.h"
#include "mtb_hal_hw_types.h"
#endif /* defined (COMPONENT_MTB_HAL) */

#if defined (CY_USING_HAL_LITE)
#include "cyhal_hw_types.h"
#endif /* defined (CY_USING_HAL_LITE) */

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

#define eth_0_ENABLED 1U
#define ETH_PHY_DP83825I 
#define eth_0_PHY_ADDR 0
#define eth_0_PHY_INTERFACE 1u
#define eth_0_PHY_SPEED 3
#define eth_0_PHY_MODE 2
#define eth_0_MAC_ADDR0 0x00U
#define eth_0_MAC_ADDR1 0x03U
#define eth_0_MAC_ADDR2 0x19U
#define eth_0_MAC_ADDR3 0x45U
#define eth_0_MAC_ADDR4 0x00U
#define eth_0_MAC_ADDR5 0x00U
#define eth_0_MAC_ADDR (((uint64_t)eth_0_MAC_ADDR0<<0) | ((uint64_t)eth_0_MAC_ADDR1<<8) | ((uint64_t)eth_0_MAC_ADDR2<<16) | ((uint64_t)eth_0_MAC_ADDR3<<24) | ((uint64_t)eth_0_MAC_ADDR4<<32) | ((uint64_t)eth_0_MAC_ADDR5<<40))
#define eth_0_STATIC_IP 0
#define eth_0_MAC_CLOCK 0u
#define eth_0_PROMISCUOUS_MODE false
#define eth_0_ACCEPT_BROADCAST_FRAMES true
#define eth_0_ETHERNET_INDEX 0
#define eth_0_INTRSRC_Q0 ((3<<16) | eth_0_interrupt_eth_0_IRQn)
#define eth_0_INTRSRC_Q1 ((3<<16) | eth_0_interrupt_eth_1_IRQn)
#define eth_0_INTRSRC_Q2 ((3<<16) | eth_0_interrupt_eth_2_IRQn)
#define eth_0_INTRMUXNUMBER 3
#define eth_0_INTRPRIORITY 3UL
#define CYCFG_TCPIP_THREAD_PRIO 4
#define CYCFG_TCPIP_THREAD_STACKSIZE 4096
#define CYCFG_IP_OPTIONS_ALLOWED 1
#define CYCFG_LWIP_IPV6 1
#define CYCFG_IP_FRAG 0
#define CYCFG_IP_REASSEMBLY 0
#define CYCFG_IP_DEFAULT_TTL 255
#define CYCFG_ARP_TABLE_SIZE 10
#define CYCFG_LWIP_AUTOIP 0
#define CYCFG_LWIP_ICMP 1
#define CYCFG_LWIP_IGMP 1
#define CYCFG_LWIP_TCP 1
#define CYCFG_TCP_MSS 1460
#define CYCFG_TCP_WND 5840
#define CYCFG_TCP_SND_BUF 5840
#define CYCFG_TCP_SND_QUEUELEN 25
#define CYCFG_LWIP_UDP 1
#define CYCFG_MEM_SIZE 1600
#define CYCFG_PBUF_POOL_SIZE 50
#define CYCFG_MEMP_NUM_PBUF 16
#define CYCFG_MEMP_NUM_RAW_PCB 4
#define CYCFG_MEMP_NUM_UDP_PCB 8
#define CYCFG_MEMP_NUM_TCP_PCB 8
#define CYCFG_MEMP_NUM_TCP_PCB_LISTEN 1
#define CYCFG_MEMP_NUM_TCP_SEG 27
#define CYCFG_MEMP_NUM_ARP_QUEUE 30
#define CYCFG_MEMP_NUM_NETBUF 8
#define CYCFG_MEMP_NUM_NETCONN 16
#define CYCFG_MEMP_NUM_TCPIP_MSG_API 8
#define CYCFG_MEMP_NUM_TCPIP_MSG_INPKT 8
#define scb_0_ENABLED 1U
#define scb_0_HW SCB0
#define scb_0_IRQ scb_0_interrupt_IRQn

extern const cy_stc_scb_uart_config_t scb_0_config;

#if defined (CY_USING_HAL) || defined(CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t scb_0_obj;
#endif /* defined (CY_USING_HAL) || defined(CY_USING_HAL_LITE) */

#if defined(CY_USING_HAL_LITE) || defined (CY_USING_HAL)
extern const cyhal_clock_t scb_0_clock;
#endif /* defined(CY_USING_HAL_LITE) || defined (CY_USING_HAL) */

#if defined (CY_USING_HAL) || defined(CY_USING_HAL_LITE)
extern const cyhal_uart_configurator_t scb_0_hal_config;
#endif /* defined (CY_USING_HAL) || defined(CY_USING_HAL_LITE) */

#if defined (COMPONENT_MTB_HAL)
extern const mtb_hal_peri_div_t scb_0_clock_ref;
extern const mtb_hal_clock_t scb_0_hal_clock;
#endif /* defined (COMPONENT_MTB_HAL) */

#if defined (COMPONENT_MTB_HAL) && (MTB_HAL_DRIVER_AVAILABLE_UART)
extern const mtb_hal_uart_configurator_t scb_0_hal_config;
#endif /* defined (COMPONENT_MTB_HAL) && (MTB_HAL_DRIVER_AVAILABLE_UART) */

void init_cycfg_peripherals(void);
void reserve_cycfg_peripherals(void);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* CYCFG_PERIPHERALS_H */
