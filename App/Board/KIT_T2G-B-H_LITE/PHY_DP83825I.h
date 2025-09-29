/*
 * Copyright (c) 2013-2025 Arm Limited. All rights reserved.
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
 * -----------------------------------------------------------------------
 *
 * $Date:        8. September 2025
 * $Revision:    V1.0
 *
 * Project:      Ethernet Physical Layer Transceiver (PHY)
 *               Definitions for DP83825I
 * -------------------------------------------------------------------- */

#ifndef __PHY_DP83825I_H
#define __PHY_DP83825I_H

#include "Driver_ETH_PHY.h"

/* Basic Registers */
#define REG_BMCR            0x00        /* Basic Mode Control Register       */
#define REG_BMSR            0x01        /* Basic Mode Status Register        */
#define REG_PHYIDR1         0x02        /* PHY Identifier 1                  */
#define REG_PHYIDR2         0x03        /* PHY Identifier 2                  */
#define REG_ANAR            0x04        /* Auto-Negotiation Advertisement    */
#define REG_ANLPAR          0x05        /* Auto-Neg. Link Partner Abitily    */
#define REG_ANER            0x06        /* Auto-Neg. Expansion Register      */
#define REG_ANNPTR          0x07        /* Auto-Neg. Next Page TX            */
#define REG_ANLNPTR         0x08
#define REG_CR1             0x09
#define REG_CR2             0x0A
#define REG_CR3             0x0B
#define REG_12              0x0C
#define REG_REGCR           0x0D
#define REG_ADDAR           0x0E
#define REG_FLDS            0x0F

/* Extended Registers */
#define REG_PHYSTS          0x10        /* Status Register                   */
#define REG_PHYSCR          0x11        /* Control Register                  */
#define REG_MISR1           0x12
#define REG_MISR2           0x13
#define REG_FCSCR           0x14
#define REG_RECR            0x15
#define REG_BISCR           0x16
#define REG_RCSR            0x17
#define REG_LEDCR           0x18
#define REG_PHYCR           0x19
#define REG_BTSCR           0x1A
#define REG_BICSR1          0x1B
#define REG_BICSR2          0x1C
#define REG_CDCR            0x1E
#define REG_PHYRCR          0x1F

/* Basic Mode Control Register */
#define BMCR_RESET          0x8000      /* Software Reset                    */
#define BMCR_LOOPBACK       0x4000      /* Loopback mode                     */
#define BMCR_SPEED_SEL      0x2000      /* Speed Select (1=100Mb/s)          */
#define BMCR_ANEG_EN        0x1000      /* Auto Negotiation Enable           */
#define BMCR_POWER_DOWN     0x0800      /* Power Down                        */
#define BMCR_ISOLATE        0x0400      /* Isolate Media interface           */
#define BMCR_REST_ANEG      0x0200      /* Restart Auto Negotiation          */
#define BMCR_DUPLEX         0x0100      /* Duplex Mode (1=Full duplex)       */
#define BMCR_COL_TEST       0x0080      /* Collision Test                    */

/* Basic Mode Status Register */
#define BMSR_100B_T4        0x8000      /* 100BASE-T4 Capable                */
#define BMSR_100B_TX_FD     0x4000      /* 100BASE-TX Full Duplex Capable    */
#define BMSR_100B_TX_HD     0x2000      /* 100BASE-TX Half Duplex Capable    */
#define BMSR_10B_T_FD       0x1000      /* 10BASE-T Full Duplex Capable      */
#define BMSR_10B_T_HD       0x0800      /* 10BASE-T Half Duplex Capable      */
#define BMSR_MF_PRE_SUP     0x0040      /* Preamble suppression Capable      */
#define BMSR_ANEG_COMPL     0x0020      /* Auto Negotiation Complete         */
#define BMSR_REM_FAULT      0x0010      /* Remote Fault                      */
#define BMSR_ANEG_ABIL      0x0008      /* Auto Negotiation Ability          */
#define BMSR_LINK_STAT      0x0004      /* Link Status (1=established)       */
#define BMSR_JABBER_DET     0x0002      /* Jaber Detect                      */
#define BMSR_EXT_CAPAB      0x0001      /* Extended Capability               */

/* PHY Identifier Registers */
#define PHY_ID1             0x2000      /* DP83825I Device Identifier MSB    */
#define PHY_ID2             0xA140      /* DP83825I Device Identifier LSB    */

/* PHY Status Register */
#define PHYSTS_MDI_X        0x4000      /* MDI-X mode enabled by Auto-Negot. */
#define PHYSTS_REC_ERR      0x2000      /* Receive Error Latch               */
#define PHYSTS_POL_STAT     0x1000      /* Polarity Status                   */
#define PHYSTS_FC_SENSE     0x0800      /* False Carrier Sense Latch         */
#define PHYSTS_SIG_DET      0x0400      /* 100Base-TX Signal Detect          */
#define PHYSTS_DES_LOCK     0x0200      /* 100Base-TX Descrambler Lock       */
#define PHYSTS_PAGE_REC     0x0100      /* Link Code Word Page Received      */
#define PHYSTS_MII_INT      0x0080      /* MII Interrupt Pending             */
#define PHYSTS_REM_FAULT    0x0040      /* Remote Fault                      */
#define PHYSTS_JABBER_DET   0x0020      /* Jabber Detect                     */
#define PHYSTS_ANEG_COMPL   0x0010      /* Auto Negotiation Complete         */
#define PHYSTS_LOOPBACK     0x0008      /* Loopback Status                   */
#define PHYSTS_DUPLEX       0x0004      /* Duplex Status (1=Full duplex)     */
#define PHYSTS_SPEED        0x0002      /* Speed10 Status (1=10MBit/s)       */
#define PHYSTS_LINK_STAT    0x0001      /* Link Status (1=established)       */

/* MII Interrupt Status Register 1 */
#define MISR1_LQ_INT        0x8000      /* Link Quality Change Interrupt     */
#define MISR1_ED_INT        0x4000      /* Energy Detect Change Interrupt    */
#define MISR1_LINK_INT      0x2000      /* Link Status Change Interrupt      */
#define MISR1_SPD_INT       0x1000      /* Speed Status Change Interrupt     */
#define MISR1_DUP_INT       0x0800      /* Duplex Status Change Interrupt    */
#define MISR1_ANC_INT       0x0400      /* Auto Negotiation Complete Interr. */
#define MISR1_FHF_INT       0x0200      /* False Carrier Counter HF Interrupt*/
#define MISR1_RHF_INT       0x0100      /* Receive Error Counter HF Interrupt*/
#define MISR1_LQ_INT_EN     0x0080      /* Link Quality Change Int.Enable    */
#define MISR1_ED_INT_EN     0x0040      /* Energy Detect Change Int.Enable   */
#define MISR1_LINK_INT_EN   0x0020      /* Link Status Change Int.Enable     */
#define MISR1_SPD_INT_EN    0x0010      /* Speed Status Change Int.Enable    */
#define MISR1_DUP_INT_EN    0x0008      /* Duplex Status Change Int.Enable   */
#define MISR1_ANC_INT_EN    0x0004      /* Auto Negotiation Complete Int.Ena.*/
#define MISR1_FHF_INT_EN    0x0002      /* False Carrier Count.HF Int.Enable */
#define MISR1_RHF_INT_EN    0x0001      /* Receive Error Count.HF Int.Enable */

/* MII Interrupt Status Register 2 */
#define MISR2_EEE_ERR_INT   0x8000      /* Energy Effic. ETH Error Interrupt */
#define MISR2_ANEG_ERR_INT  0x4000      /* Auto Negotiation Error Interrupt  */
#define MISR2_PAGE_REC_INT  0x2000      /* Page Received Interrupt           */
#define MISR2_LP_FIFO_INT   0x1000      /* Loopb FIFO OF/UF Interrupt        */
#define MISR2_MDI_CR_INT    0x0800      /* MDI/MDIX Status Change Interrupt  */
#define MISR2_SLEEP_INT     0x0400      /* Sleep Mode Event Interrupt        */
#define MISR2_INV_POL_INT   0x0200      /* Inverted Polarity Interrupt       */
#define MISR2_JABBER_INT    0x0100      /* Jabber Detect Interrupt           */
#define MISR2_EEE_ERR_EN    0x0080      /* Energy Effic. ETH Error Int.Enable*/
#define MISR2_ANEG_ERR_EN   0x0040      /* Auto Neg. Error Int.Enable        */
#define MISR2_PAGE_REC_EN   0x0020      /* Page Received Int.Enable          */
#define MISR2_LP_FIFO_EN    0x0010      /* Loopb FIFO OF/UF Int.Enable       */
#define MISR2_MDI_CR_EN     0x0008      /* MDI/MDIX Status Change Int.Enable */
#define MISR2_SLEEP_EN      0x0004      /* Sleep Mode Event Int.Enable       */
#define MISR2_INV_POL_EN    0x0002      /* Inverted Polarity Int.Enable      */
#define MISR2_JABBER_EN     0x0001      /* Jabber Detect Int.Enable          */

/* LED Direct Control Register */
#define LEDCR_BLINK_RATE    0x0600      /* LED Blinking Rate                 */
#define LEDCR_LINK_POL      0x0080      /* LED Link Polarity                 */
#define LEDCR_DRV_LINK_LED  0x0010      /* Drive Link LED Select             */
#define LEDCR_LINK_LED_VAL  0x0002      /* Value to force on LED_LINK output */

/* PHY Control Register */
#define PHYCR_MDIX_EN       0x8000      /* Auto MDIX Enable                  */
#define PHYCR_FORCE_MDIX    0x4000      /* Force MDIX                        */
#define PHYCR_PAUSE_RX      0x2000      /* Pause Receive Negotiated          */
#define PHYCR_PAUSE_TX      0x1000      /* Pause Transmit Negotiated         */
#define PHYCR_MII_LINK      0x0800      /* MII Link Status                   */
#define PHYCR_BP_STRETCH    0x0080      /* Bypass LED Stretching             */
#define PHYCR_LED_CNFG      0x0020      /* LEDs Configuration                */
#define PHYCR_PHYADDR       0x001F      /* PHY Address for port              */

/* 10Base-T Status/Control Register */
#define BTSCR_REC_TH_EN     0x2000      /* Lower Receiver Threshold Enable   */
#define BTSCR_SQUELCH       0x0E00      /* Squelch Configuration             */
#define BTSCR_NLP_DIS       0x0080      /* Normal Link Pulse Disable         */
#define BTSCR_POLARITY      0x0010      /* 10Mbs Polarity Status             */
#define BTSCR_JABBER_DIS    0x0001      /* Jabber Disable                    */

//* BISCR Register */
#define BISCR_REV_LOOPB     0x0010      /* Reverse loopback                  */
#define BISCR_ANALOG_LOOPB  0x0008      /* Analog loopback                   */
#define BISCR_DIGITAL_LOOPB 0x0004      /* Digital loopback (100Base-TX only)*/
#define BISCR_PCS_OUT_LOOPB 0x0002      /* PCS output loopback               */
#define BISCR_PCS_IN_LOOPB  0x0001      /* PCS input loopback (10Base-T only)*/

/* PHYRCR Register */
#define PHYRCR_HARD_RESET   0x8000      /* Software Hard Reset               */
#define PHYRCR_DIG_RESET    0x4000      /* Digital Reset                     */

/* PHY Driver State Flags */
#define PHY_INIT            0x01U       /* Driver initialized                */
#define PHY_POWER           0x02U       /* Driver power is on                */

/* PHY Driver Control Structure */
typedef struct phy_ctrl {
  ARM_ETH_PHY_Read_t  reg_rd;           /* PHY register read function        */
  ARM_ETH_PHY_Write_t reg_wr;           /* PHY register write function       */
  uint16_t            bmcr;             /* BMCR register value               */
  uint8_t             flags;            /* Control flags                     */
  uint8_t             rsvd;             /* Reserved                          */
} PHY_CTRL;

#endif /* __PHY_DP83825I_H */
