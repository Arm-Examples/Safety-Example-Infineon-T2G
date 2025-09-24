#ifndef __EMAC_T2G_H
#define __EMAC_T2G_H

#include "Driver_ETH_MAC.h"

/* EMAC Driver state flags */
#define EMAC_FLAG_INIT      (1 << 0)    // Driver initialized
#define EMAC_FLAG_POWER     (1 << 1)    // Driver power on
#define EMAC_FLAG_DMA_INIT  (1 << 2)    // DMA Initialized



/* EMAC Driver Control Information */
typedef struct {
  ARM_ETH_MAC_SignalEvent_t cb_event;   // Event callback
  uint8_t       flags;                  // Control and state flags
  uint8_t       tx_index;               // Transmit descriptor index
  uint8_t       rx_index;               // Receive descriptor index
#if (EMAC_CHECKSUM_OFFLOAD)
  bool          tx_cks_offload;         // Checksum offload enabled/disabled
#endif
#if (EMAC_TIME_STAMP)
  uint8_t       tx_ts_index;            // Transmit Timestamp descriptor index
#endif
  uint8_t      *frame_end;              // End of assembled frame fragments
} EMAC_CTRL;


// Global functions and variables exported by driver .c module
extern ARM_DRIVER_ETH_MAC Driver_ETH_MAC0;
#endif /* __EMAC_T2G_H */