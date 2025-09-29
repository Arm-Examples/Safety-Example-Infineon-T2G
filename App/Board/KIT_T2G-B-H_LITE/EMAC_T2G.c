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
 * Driver:       Driver_ETH_MAC0
 * Project:      CMSIS Ethernet Media Access (MAC) Driver Infineon Traveo T2G
 * --------------------------------------------------------------------------
 * Use the following configuration settings in the middleware component
 * to connect to this driver.
 *
 *   Configuration Setting                     Value
 *   ---------------------                     -----
 *   Connect to hardware via Driver_ETH_MAC# = 0
 * -------------------------------------------------------------------------- */

/* History:
 *  Version 1.0
 *    Initial release
 */

#include <string.h>
#include "EMAC_T2G.h"
#include "cy_ethif.h"
#include "cy_sysint.h"

/* Needed for C*/
extern void cy_ethif_privatedata;

/* Receive/transmit checksum offload enabled by default */
#ifndef EMAC_CHECKSUM_OFFLOAD
  #define EMAC_CHECKSUM_OFFLOAD 1
#endif

#define ARM_ETH_MAC_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0) /* driver version */

/* EMAC Memory Buffer configuration */
#define EMAC_BUF_SIZE           (CY_ETH_SIZE_MAX_FRAME)
#define EMAC_RX_BUF_CNT         ((CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE * 3) / 2)
#define EMAC_TX_BUF_CNT         (CY_ETH_DEFINE_TOTAL_BD_PER_TXQUEUE)

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
  ARM_ETH_MAC_API_VERSION,
  ARM_ETH_MAC_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_ETH_MAC_CAPABILITIES DriverCapabilities = {
  (EMAC_CHECKSUM_OFFLOAD) ? 1U : 0U,    /* checksum_offload_rx_ip4  */
  (EMAC_CHECKSUM_OFFLOAD) ? 1U : 0U,    /* checksum_offload_rx_ip6  */
  (EMAC_CHECKSUM_OFFLOAD) ? 1U : 0U,    /* checksum_offload_rx_udp  */
  (EMAC_CHECKSUM_OFFLOAD) ? 1U : 0U,    /* checksum_offload_rx_tcp  */
  0U,                                   /* checksum_offload_rx_icmp */
  (EMAC_CHECKSUM_OFFLOAD) ? 1U : 0U,    /* checksum_offload_tx_ip4  */
  (EMAC_CHECKSUM_OFFLOAD) ? 1U : 0U,    /* checksum_offload_tx_ip6  */
  (EMAC_CHECKSUM_OFFLOAD) ? 1U : 0U,    /* checksum_offload_tx_udp  */
  (EMAC_CHECKSUM_OFFLOAD) ? 1U : 0U,    /* checksum_offload_tx_tcp  */
  0U,                                   /* checksum_offload_tx_icmp */
  ARM_ETH_INTERFACE_RMII,               /* media_interface          */
  0U,                                   /* mac_address              */
  1U,                                   /* event_rx_frame           */
  1U,                                   /* event_tx_frame           */
  1U,                                   /* event_wakeup             */
  0U,                                   /* precision_timer          */
  0U                                    /* reserved                 */
};

/* EMAC control structure */
static EMAC_CTRL emac = { 0 };

/* Frame buffers */
struct RxFrameBuffer {
  /* The maximum size of an Ethernet frame is 1522 bytes including VLAN and FCS. */
  /* It is safe to place the frame length in the last 4 bytes of the frame.      */
  uint8_t  Buffer[EMAC_BUF_SIZE-4];
  uint32_t Length;
}       Rx_Buf[EMAC_RX_BUF_CNT] __ALIGNED(32);
uint8_t Tx_Buf[EMAC_TX_BUF_CNT][EMAC_BUF_SIZE] __ALIGNED(32);

static void eth0_rx_frame_cb (ETH_Type *base, uint8_t *rx_buffer, uint32_t length) {
  (void)base;

  /* Queue the received frame, no FCS */
  Rx_Buf[emac.rx_head].Length = length - 4U;

  /* rx_buffer is at rx_head position */
  (void)rx_buffer;

  /* Increment head index of received frames */
  if (++emac.rx_head >= EMAC_RX_BUF_CNT) {
    emac.rx_head = 0U;
  }

  /* Notify the applicaton */
  if (emac.cb_event != NULL) {
    emac.cb_event (ARM_ETH_MAC_EVENT_RX_FRAME);
  }
}

static void eth0_rx_get_buff (ETH_Type *base, uint8_t **buffer, uint32_t *length) {
  (void)base;

  /* Check if buffer available */
  if (emac.rx_index == emac.rx_tail) {
    return;
  }

  *buffer = Rx_Buf[emac.rx_index].Buffer;
  *length = sizeof(Rx_Buf[0]);

  if (++emac.rx_index >= EMAC_RX_BUF_CNT) {
    emac.rx_index = 0U;
  }
}

static void eth0_tx_complete_cb (ETH_Type *base, uint8_t queue_index) {
  (void)base;
  (void)queue_index;

  /* Notify the applicaton */
  if (emac.cb_event != NULL) {
    emac.cb_event (ARM_ETH_MAC_EVENT_TX_FRAME);
  }
}

static const cy_stc_ethif_cb_t stcInterruptCB = {
  .rxframecb      = eth0_rx_frame_cb,
  .txerrorcb      = NULL,
  .txcompletecb   = eth0_tx_complete_cb,
  .tsuSecondInccb = NULL,
  .rxgetbuff      = eth0_rx_get_buff
};

static const cy_stc_sysint_t irq_cfg_ethx_q0 = {
  .intrSrc      = ((NvicMux3_IRQn << 16) | eth_0_interrupt_eth_0_IRQn),
  .intrPriority = 1U
};
static const cy_stc_sysint_t irq_cfg_ethx_q1 = {
  .intrSrc      = ((NvicMux3_IRQn << 16) | eth_0_interrupt_eth_1_IRQn),
  .intrPriority = 1U
};
static const cy_stc_sysint_t irq_cfg_ethx_q2 = {
  .intrSrc      = ((NvicMux3_IRQn << 16) | eth_0_interrupt_eth_2_IRQn),
  .intrPriority = 1U
};

static void Eth0_InterruptHandler (void);

/**
  \fn          ARM_DRIVER_VERSION GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION
*/
static ARM_DRIVER_VERSION GetVersion (void) {
  return DriverVersion;
}

/**
  \fn          ARM_ETH_MAC_CAPABILITIES GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref ARM_ETH_MAC_CAPABILITIES
*/
static ARM_ETH_MAC_CAPABILITIES GetCapabilities (void) {
  return DriverCapabilities;
}

/**
  \fn          int32_t Initialize (ARM_ETH_MAC_SignalEvent_t cb_event)
  \brief       Initialize Ethernet MAC Device.
  \param[in]   cb_event  Pointer to \ref ARM_ETH_MAC_SignalEvent
  \return      \ref execution_status
*/
static int32_t Initialize (ARM_ETH_MAC_SignalEvent_t cb_event) {

  if (emac.flags & EMAC_FLAG_INIT) {
    return ARM_DRIVER_OK;
  }

  /* Clear control structure */
  memset (&emac, 0, sizeof (EMAC_CTRL));
  
   /* Register driver callback function */
  emac.cb_event = cb_event;

  /* Register CEDI driver API and instance */
  emac.base     = ETH0;
  emac.drv      = CEDI_GetInstance ();
  emac.pd       = &cy_ethif_privatedata;

  emac.flags    = EMAC_FLAG_INIT;

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t Uninitialize (void)
  \brief       De-initialize Ethernet MAC Device.
  \return      \ref execution_status
*/
static int32_t Uninitialize (void) {

  emac.flags = 0U;

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t PowerControl (ARM_POWER_STATE state)
  \brief       Control Ethernet MAC Device Power.
  \param[in]   state  Power state
  \return      \ref execution_status
*/
static int32_t PowerControl (ARM_POWER_STATE state) {
  cy_stc_ethif_mac_config_t     stcEnetConfig      = { 0 };
  cy_stc_ethif_intr_config_t    stcInterruptConfig = { 0 };
  cy_stc_ethif_wrapper_config_t stcWrapperConfig   = { 0 };
  cy_ethif_buffpool_t           RxBufPool;
  uint32_t i;

  switch (state) {
    case ARM_POWER_OFF:
      if (!(emac.flags & EMAC_FLAG_POWER)) {
        break;
      }

      /* Disable EMAC interrupts in NVIC */
      NVIC_DisableIRQ (NvicMux3_IRQn);

      /* Disable Ethernet MAC */
      emac.drv->destroy (emac.pd);
      ETH_CTL(emac.pd) &= ~ETH_CTL_ENABLED_Msk;

      emac.flags = EMAC_FLAG_INIT;
      break;

    case ARM_POWER_LOW:
      return ARM_DRIVER_ERROR_UNSUPPORTED;

    case ARM_POWER_FULL:
      if (!(emac.flags & EMAC_FLAG_INIT)) {
        return ARM_DRIVER_ERROR;
      }
      if (emac.flags & EMAC_FLAG_POWER) {
        break;
      }

      /* Configure EMAC peripheral interrupts in NVIC */
      Cy_SysInt_Init (&irq_cfg_ethx_q0, Eth0_InterruptHandler);
      Cy_SysInt_Init (&irq_cfg_ethx_q1, Eth0_InterruptHandler);
      Cy_SysInt_Init (&irq_cfg_ethx_q2, Eth0_InterruptHandler);

      /* General Ethernet configuration */
      for (i = 0U; i < CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE; i++) {
        RxBufPool[i] = Rx_Buf[i].Buffer;
      }
      stcWrapperConfig.stcInterfaceSel = CY_ETHIF_CTL_RMII_100;
      stcWrapperConfig.bRefClockSource = CY_ETHIF_EXTERNAL_HSIO;
      stcWrapperConfig.u8RefClkDiv     = 1;

      stcEnetConfig.bintrEnable       = 1;                          /* Interrupt enable  */
      stcEnetConfig.dmaDataBurstLen   = CY_ETHIF_DMA_DBUR_LEN_4;
      stcEnetConfig.u8dmaCfgFlags     = CY_ETHIF_CFG_DMA_FRCE_TX_BRST;
      stcEnetConfig.mdcPclkDiv        = CY_ETHIF_MDC_DIV_BY_32;     /* Source clock 80 MHz, MDC must be less than 2.5MHz */
      stcEnetConfig.u8rx1536ByteEn    = 1;                          /* Enable receive frame up to 1536  */
      stcEnetConfig.u8enRxBadPreamble = 1;
      stcEnetConfig.u8aw2wMaxPipeline = 2;                          /* Value must be > 0 */
      stcEnetConfig.u8ar2rMaxPipeline = 2;                          /* Value must be > 0 */
      stcEnetConfig.pstcWrapperConfig = &stcWrapperConfig;
      stcEnetConfig.btxq0enable       = 1;                          /* Tx Q0 Enabled */
      stcEnetConfig.brxq0enable       = 1;                          /* Rx Q0 Enabled */
      stcEnetConfig.pRxQbuffPool[0]   = &RxBufPool;

      /* Interrupt configurations */
      stcInterruptConfig.btx_complete           = 1;                /* Frame has been transmitted successfully */
      stcInterruptConfig.btx_fr_corrupt         = 1;                /* Tx frame corrupted                      */
      stcInterruptConfig.btx_retry_ex_late_coll = 1;                /* Retry limit exceeded or late collision  */
      stcInterruptConfig.btx_underrun           = 1;                /* Tx underrun                             */
      stcInterruptConfig.brx_complete           = 1;                /* Frame received successfully and stored  */

      if (Cy_ETHIF_Init (emac.base, &stcEnetConfig, &stcInterruptConfig) != CY_ETHIF_SUCCESS) {
        return ARM_DRIVER_ERROR;
      }
      Cy_ETHIF_RegisterCallbacks (emac.base, (cy_stc_ethif_cb_t *)&stcInterruptCB);

      emac.rx_index = 4U;
      emac.rx_head  = 0U;
      emac.rx_tail  = 0U;

      /* Enable EMAC peripheral interrupts in NVIC */
      NVIC_EnableIRQ (NvicMux3_IRQn);

      emac.flags |= EMAC_FLAG_POWER;
      break;

    default:
      return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t GetMacAddress (ARM_ETH_MAC_ADDR *ptr_addr)
  \brief       Get Ethernet MAC Address.
  \param[in]   ptr_addr  Pointer to address
  \return      \ref execution_status
*/
static int32_t GetMacAddress (ARM_ETH_MAC_ADDR *ptr_addr) {
  uint8_t dmy[2];

  if (ptr_addr == NULL) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  emac.drv->getSpecificAddr (emac.pd, CY_ETHIF_FILTER_NUM_1, (CEDI_MacAddress *)ptr_addr, &dmy[0], &dmy[1]);
   
  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t SetMacAddress (const ARM_ETH_MAC_ADDR *ptr_addr)
  \brief       Set Ethernet MAC Address.
  \param[in]   ptr_addr  Pointer to address
  \return      \ref execution_status
*/
static int32_t SetMacAddress (const ARM_ETH_MAC_ADDR *ptr_addr) {

  if (ptr_addr == NULL) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (!(emac.flags & EMAC_FLAG_POWER)) {
    return ARM_DRIVER_ERROR;
  }

  emac.drv->setSpecificAddr (emac.pd, CY_ETHIF_FILTER_NUM_1, (CEDI_MacAddress *)ptr_addr, 0U, 0U);

  return ARM_DRIVER_OK;
}

/**
  \fn          uint32_t crc32_8bit_rev (uint32_t crc32, uint8_t val)
  \brief       Calculate 32-bit CRC (Polynomial: 0x04C11DB7, data bit-reversed).
  \param[in]   crc32  CRC initial value
  \param[in]   val    Input value
  \return      Calculated CRC value
*/
static uint32_t crc32_8bit_rev (uint32_t crc32, uint8_t val) {
  uint32_t n;

  crc32 ^= __RBIT (val);
  for (n = 8; n; n--) {
    if (crc32 & 0x80000000U) {
      crc32 <<= 1;
      crc32  ^= 0x04C11DB7U;
    } else {
      crc32 <<= 1;
    }
  }
  return (crc32);
}

/**
  \fn          uint32_t crc32_data (const uint8_t *data, uint32_t len)
  \brief       Calculate standard 32-bit Ethernet CRC.
  \param[in]   data  Pointer to buffer containing the data
  \param[in]   len   Data length in bytes
  \return      Calculated CRC value
*/
static uint32_t crc32_data (const uint8_t *data, uint32_t len) {
  uint32_t cnt, crc;

  crc = 0xFFFFFFFFU;
  for (cnt = len; cnt; cnt--) {
    crc = crc32_8bit_rev (crc, *data++);
  }
  return (crc ^ 0xFFFFFFFFU);
}

/**
  \fn          int32_t SetAddressFilter (const ARM_ETH_MAC_ADDR *ptr_addr,
                                               uint32_t          num_addr)
  \brief       Configure Address Filter.
  \param[in]   ptr_addr  Pointer to addresses
  \param[in]   num_addr  Number of addresses to configure
  \return      \ref execution_status
*/
static int32_t SetAddressFilter (const ARM_ETH_MAC_ADDR *ptr_addr, uint32_t num_addr) {
  CEDI_MacAddress mac_null = { 0 };
  uint32_t crc, hash_top, hash_bottom;

  if ((ptr_addr == NULL) && (num_addr != 0)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (!(emac.flags & EMAC_FLAG_POWER)) {
    return ARM_DRIVER_ERROR;
  }

  if (num_addr < 4) {
    /* No hash filtering */
    emac.drv->setMulticastEnable (emac.pd, 0U);
    emac.flags &= ~EMAC_FLAG_FILTER;
  }

  /* Use specific address filter for the 3 MAC addresses */
  if (num_addr == 0U) {
    emac.drv->setSpecificAddr (emac.pd, CY_ETHIF_FILTER_NUM_2, &mac_null, 0U, 0U);
    emac.drv->setSpecificAddr (emac.pd, CY_ETHIF_FILTER_NUM_3, &mac_null, 0U, 0U);
    emac.drv->setSpecificAddr (emac.pd, CY_ETHIF_FILTER_NUM_4, &mac_null, 0U, 0U);
    return ARM_DRIVER_OK;
  }

  emac.drv->setSpecificAddr (emac.pd, CY_ETHIF_FILTER_NUM_2, (CEDI_MacAddress *)ptr_addr, 0U, 0U);
  if (num_addr == 1U) {
    emac.drv->setSpecificAddr (emac.pd, CY_ETHIF_FILTER_NUM_3, &mac_null, 0U, 0U);
    emac.drv->setSpecificAddr (emac.pd, CY_ETHIF_FILTER_NUM_4, &mac_null, 0U, 0U);
    return ARM_DRIVER_OK;
  }
  ptr_addr++;

  emac.drv->setSpecificAddr (emac.pd, CY_ETHIF_FILTER_NUM_3, (CEDI_MacAddress *)ptr_addr, 0U, 0U);
  if (num_addr == 2U) {
    emac.drv->setSpecificAddr (emac.pd, CY_ETHIF_FILTER_NUM_4, &mac_null, 0U, 0U);
    return ARM_DRIVER_OK;
  }
  ptr_addr++;

  emac.drv->setSpecificAddr (emac.pd, CY_ETHIF_FILTER_NUM_4, (CEDI_MacAddress *)ptr_addr, 0U, 0U);
  if (num_addr == 3U) {
    return ARM_DRIVER_OK;
  }
  ptr_addr++;

  /* Calculate 64-bit Hash table for remaining MAC addresses */
  hash_top = hash_bottom = 0U;
  for ( ; num_addr > 3U; ptr_addr++, num_addr--) {
    crc = crc32_data (&ptr_addr->b[0], 6U) >> 26;
    if (crc & 0x20U) {
      hash_top    |= (1U << (crc & 0x1FU));
    }
    else {
      hash_bottom |= (1U << crc);
    }
  }

  /* Setup multicast hash filtering */
  emac.drv->setHashAddr (emac.pd, hash_top, hash_bottom);
  emac.drv->setMulticastEnable (emac.pd, 1U);
  emac.flags |= EMAC_FLAG_FILTER;

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t SendFrame (const uint8_t *frame, uint32_t len, uint32_t flags)
  \brief       Send Ethernet frame.
  \param[in]   frame  Pointer to frame buffer with data to send
  \param[in]   len    Frame buffer length in bytes
  \param[in]   flags  Frame transmit flags (see ARM_ETH_MAC_TX_FRAME_...)
  \return      \ref execution_status
*/
static int32_t SendFrame (const uint8_t *frame, uint32_t len, uint32_t flags) {
  uint16_t tx_free;

  if ((frame == NULL) || (len == 0U)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (!(emac.flags & EMAC_FLAG_POWER)) {
    return ARM_DRIVER_ERROR;
  }

  if (emac.tx_len == 0U) {
    /* Start of a new transmit frame */
    emac.drv->txDescFree (emac.pd, 0, &tx_free);
    if (tx_free == 0U) {
      /* Transmitter is busy, wait */
      return ARM_DRIVER_ERROR_BUSY;
    }
  }
  
  /* Copy data fragments to TX data buffer */
  memcpy (&Tx_Buf[emac.tx_index] + emac.tx_len, frame, len);
  emac.tx_len += len;

  if (flags & ARM_ETH_MAC_TX_FRAME_FRAGMENT) {
    /* More data to come */
    return ARM_DRIVER_OK;
  }

  /* Frame is now ready, add it to the TX queue */
  Cy_ETHIF_TransmitFrame (emac.base, Tx_Buf[emac.tx_index], len, CY_ETH_QS0_0, 1);

  if (++emac.tx_index >= EMAC_TX_BUF_CNT) {
    emac.tx_index = 0U;
  }
  emac.tx_len = 0U;

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t ReadFrame (uint8_t *frame, uint32_t len)
  \brief       Read data of received Ethernet frame.
  \param[in]   frame  Pointer to frame buffer for data to read into
  \param[in]   len    Frame buffer length in bytes
  \return      number of data bytes read or execution status
                 - value >= 0: number of data bytes read
                 - value < 0: error occurred, value is execution status as defined with \ref execution_status 
*/
static int32_t ReadFrame (uint8_t *frame, uint32_t len) {

  if ((frame == NULL) && (len != 0U)) {
    /* Invalid parameters */
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  if (!(emac.flags & EMAC_FLAG_POWER)) {
    return ARM_DRIVER_ERROR;
  }

  memcpy (frame, Rx_Buf[emac.rx_tail].Buffer, len);

  if (++emac.rx_tail >= EMAC_RX_BUF_CNT) {
    emac.rx_tail = 0U;
  }

  return (int32_t)len;
}

/**
  \fn          uint32_t GetRxFrameSize (void)
  \brief       Get size of received Ethernet frame.
  \return      number of bytes in received frame
*/
static uint32_t GetRxFrameSize (void) {
  
  if (!(emac.flags & EMAC_FLAG_POWER)) {
    return ARM_DRIVER_ERROR;
  }

  /* Check if frame is available */
  if (emac.rx_tail == emac.rx_head) {
    return 0U;
  }

  return Rx_Buf[emac.rx_tail].Length;
}

/**
  \fn          int32_t GetRxFrameTime (ARM_ETH_MAC_TIME *time)
  \brief       Get time of received Ethernet frame.
  \param[in]   time  Pointer to time structure for data to read into
  \return      \ref execution_status
*/
static int32_t GetRxFrameTime (ARM_ETH_MAC_TIME *time) {
  (void)time;

  return ARM_DRIVER_ERROR_UNSUPPORTED;
}

/**
  \fn          int32_t GetTxFrameTime (ARM_ETH_MAC_TIME *time)
  \brief       Get time of transmitted Ethernet frame.
  \param[in]   time  Pointer to time structure for data to read into
  \return      \ref execution_status
*/
static int32_t GetTxFrameTime (ARM_ETH_MAC_TIME *time) {
  (void)time;

  /* Not implemented */
  return ARM_DRIVER_ERROR_UNSUPPORTED;
}

/**
  \fn          int32_t Control (uint32_t control, uint32_t arg)
  \brief       Control Ethernet Interface.
  \param[in]   control  operation
  \param[in]   arg      argument of operation (optional)
  \return      \ref execution_status
*/
static int32_t Control (uint32_t control, uint32_t arg) {

  if (!(emac.flags & EMAC_FLAG_POWER)) {
    return ARM_DRIVER_ERROR;
  }

  switch (control) {
    case ARM_ETH_MAC_CONFIGURE:
      /* Configure 100MBit/10MBit mode */
      switch (arg & ARM_ETH_MAC_SPEED_Msk) {
        case ARM_ETH_MAC_SPEED_10M:
          emac.drv->setIfSpeed (emac.pd, CEDI_SPEED_10M);
          break;
        case ARM_ETH_SPEED_100M:
          emac.drv->setIfSpeed (emac.pd, CEDI_SPEED_100M);
          break;
        default:
          return ARM_DRIVER_ERROR_UNSUPPORTED;
      }

      /* Configure Half/Full duplex mode */
      switch (arg & ARM_ETH_MAC_DUPLEX_Msk) {
        case ARM_ETH_MAC_DUPLEX_HALF:
          emac.drv->setFullDuplex (emac.pd, 0U);
          break;
        case ARM_ETH_MAC_DUPLEX_FULL:
          emac.drv->setFullDuplex (emac.pd, 1U);
          break;
      }
#if 0
      /* Configure loopback mode */
      if (arg & ARM_ETH_MAC_LOOPBACK) {
        emac.drv->setLoopback (emac.pd, CEDI_LOCAL_LOOPBACK);
      }
      else {
        emac.drv->setLoopback (emac.pd, CEDI_NO_LOOPBACK);
      }
#endif
#if (EMAC_CHECKSUM_OFFLOAD)
      /* Enable rx checksum verification */
      if (arg & ARM_ETH_MAC_CHECKSUM_OFFLOAD_RX) {
        emac.drv->setRxChecksumOffload (emac.pd, 1U);
      }
      else {
        emac.drv->setRxChecksumOffload (emac.pd, 0U);
      }

      /* Enable tx checksum generation */
      if (arg & ARM_ETH_MAC_CHECKSUM_OFFLOAD_TX) {
        emac.drv->setTxChecksumOffload (emac.pd, 1U);
      }
      else {
        emac.drv->setTxChecksumOffload (emac.pd, 0U);
      }
#else
      if ((arg & ARM_ETH_MAC_CHECKSUM_OFFLOAD_RX) ||
          (arg & ARM_ETH_MAC_CHECKSUM_OFFLOAD_TX)) {
        /* Checksum offload is disabled in the driver */
        return ARM_DRIVER_ERROR;
      }
#endif

      /* Configure broadcast receive */
      if (arg & ARM_ETH_MAC_ADDRESS_BROADCAST) {
        emac.drv->setNoBroadcast (emac.pd, 0U);
      }
      else {
        emac.drv->setNoBroadcast (emac.pd, 1U);
      }

      /* Configure all multicast receive */
      if (emac.flags & EMAC_FLAG_FILTER) {
        /* Hash filter already used */
        return ARM_DRIVER_ERROR;
      }
      if (arg & ARM_ETH_MAC_ADDRESS_MULTICAST) {
        /* Enable all addresses in hash filter */
        emac.drv->setHashAddr (emac.pd, 0xFFFFFFFF, 0xFFFFFFFF);
        emac.drv->setMulticastEnable (emac.pd, 1U);
      }
      else {
        emac.drv->setMulticastEnable (emac.pd, 0U);
      }

      /* Enable promiscuous mode (no filtering) */
      if (arg & ARM_ETH_MAC_ADDRESS_ALL) {
        emac.drv->setCopyAllFrames (emac.pd, 1U);
      }
      else {
        emac.drv->setCopyAllFrames (emac.pd, 0U);
      }
      break;

    case ARM_ETH_MAC_CONTROL_TX:
      /* Enable/disable MAC transmitter */
      if (arg != 0U) {
        emac.drv->enableTx (emac.pd);
      }
      else {
        emac.drv->abortTx (emac.pd);
      }
      break;

    case ARM_ETH_MAC_CONTROL_RX:
      /* Enable/disable MAC receiver */
      if (arg != 0U) {
        emac.drv->enableRx (emac.pd);
      }
      else {
        emac.drv->disableRx (emac.pd);
      }
      break;

    case ARM_ETH_MAC_FLUSH:
      /* Flush Tx and Rx buffers */
      if (arg & ARM_ETH_MAC_FLUSH_RX) {

      }
      if (arg & ARM_ETH_MAC_FLUSH_TX) {

      }
      break;

    case ARM_ETH_MAC_SLEEP:
      /* Enable/disable Sleep mode */
      if (arg != 0U) {

      }
      else {

      }
      break;

    case ARM_ETH_MAC_VLAN_FILTER:
      /* Configure VLAN filter */
      if (arg != 0U) {
        /* Enable VLAN filtering */
        emac.drv->setVlanOnly (emac.pd, 1U);
        emac.drv->setStackedVlanReg (emac.pd, 1U, arg & 0xFFFF);
      }  
      else {
        /* Disable VLAN filtering */
        emac.drv->setVlanOnly (emac.pd, 0U);
        emac.drv->setStackedVlanReg (emac.pd, 0U, 0U);
      } 
      break;

    default:
      return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t ControlTimer (uint32_t control, ARM_ETH_MAC_TIME *time)
  \brief       Control Precision Timer.
  \param[in]   control  operation
  \param[in]   time     Pointer to time structure
  \return      \ref execution_status
*/
static int32_t ControlTimer (uint32_t control, ARM_ETH_MAC_TIME *time) {
  (void)control;
  (void)time;

  /* Not implemented */
  return ARM_DRIVER_ERROR_UNSUPPORTED;
}

/**
  \fn          int32_t PHY_Read (uint8_t phy_addr, uint8_t reg_addr, uint16_t *data)
  \brief       Read Ethernet PHY Register through Management Interface.
  \param[in]   phy_addr  5-bit device address
  \param[in]   reg_addr  5-bit register address
  \param[out]  data      Pointer where the result is written to
  \return      \ref execution_status
*/
static int32_t PHY_Read (uint8_t phy_addr, uint8_t reg_addr, uint16_t *data) {
  uint32_t loop;
  
  if (data == NULL) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }
  if (!(emac.flags & EMAC_FLAG_POWER)) {
    return ARM_DRIVER_ERROR;
  }

  emac.drv->phyStartMdioRead (emac.pd, CY_ETHIF_PHY_FLAG, phy_addr, reg_addr);

  /* Wait until operation completed */
  loop = SystemCoreClock >> 12;
  while (!emac.drv->getMdioIdle (emac.pd)) {
    loop--;
    if (loop == 0) {
      /* Loop counter timeout */
      return ARM_DRIVER_ERROR_TIMEOUT;
    }
  }
  emac.drv->getMdioReadData (emac.pd, data);

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t PHY_Write (uint8_t phy_addr, uint8_t reg_addr, uint16_t data)
  \brief       Write Ethernet PHY Register through Management Interface.
  \param[in]   phy_addr  5-bit device address
  \param[in]   reg_addr  5-bit register address
  \param[in]   data      16-bit data to write
  \return      \ref execution_status
*/
static int32_t PHY_Write (uint8_t phy_addr, uint8_t reg_addr, uint16_t data) {
  uint32_t loop;

  if (!(emac.flags & EMAC_FLAG_POWER)) {
    return ARM_DRIVER_ERROR;
  }

  emac.drv->phyStartMdioWrite (emac.pd, CY_ETHIF_PHY_FLAG, phy_addr, reg_addr, data);

  /* Wait until operation completed */
  loop = SystemCoreClock >> 12;
  while (!emac.drv->getMdioIdle (emac.pd)) {
    loop--;
    if (loop == 0) {
      /* Loop counter timeout */
      return ARM_DRIVER_ERROR_TIMEOUT;
    }
  }
  return ARM_DRIVER_OK;
}

/**
  \fn          void Eth0_InterruptHandler (void)
  \brief       Ethernet Interrupt handler.
*/
static void Eth0_InterruptHandler (void) {
  emac.drv->isr (emac.pd);
}

/* MAC Driver Control Block */
ARM_DRIVER_ETH_MAC Driver_ETH_MAC0 = {
  GetVersion,
  GetCapabilities,
  Initialize,
  Uninitialize,
  PowerControl,
  GetMacAddress,
  SetMacAddress,
  SetAddressFilter,
  SendFrame,
  ReadFrame,
  GetRxFrameSize,
  GetRxFrameTime,
  GetTxFrameTime,
  ControlTimer,
  Control,
  PHY_Read,
  PHY_Write
};
