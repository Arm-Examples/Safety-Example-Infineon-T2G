/* -------------------------------------------------------------------------- 
 * Copyright (c) 2019-2025 Arm Limited (or its affiliates).
 * All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 * $Date:        18. September 2025
 * $Revision:    V1.0
 *
 * Project:      Ethernet Media Access (MAC) Definitions for Infineon Traveo T2G
 * -------------------------------------------------------------------------- */

#ifndef EMAC_T2G_H__
#define EMAC_T2G_H__

#include "Driver_ETH_MAC.h"
#include "cedi.h"

/* EMAC Driver state flags */
#define EMAC_FLAG_INIT     (1U << 0)        // Driver initialized
#define EMAC_FLAG_POWER    (1U << 1)        // Driver power on
#define EMAC_FLAG_FILTER   (1U << 2)        // Multicast hash filer active

/* EMAC Driver Control Information */
typedef struct {
  ARM_ETH_MAC_SignalEvent_t cb_event;       // Event callback
  uint8_t                   flags;          // Control and state flags
  uint8_t                   rx_index;       // Receive buffer index
  uint8_t                   rx_head;        // Consumer head index
  uint8_t                   rx_tail;        // Consumer tail index
  uint8_t                   tx_index;       // Transmit buffer index
  uint32_t                  tx_len;         // Length of assembled frame fragments
  void                     *base;           // EMAC peripheral base address
  CEDI_OBJ                 *drv;            // Driver object pointer (CEDI APIs)
  void                     *pd;             // Driver private data info
} EMAC_CTRL;

// Global functions and variables exported by driver .c module
extern ARM_DRIVER_ETH_MAC Driver_ETH_MAC0;
#endif /* EMAC_T2G_H__ */
