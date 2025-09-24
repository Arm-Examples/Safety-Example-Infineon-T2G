#include "EMAC_T2G.h"
#include "Driver_ETH_PHY.h"             // CMSIS Driver:Ethernet PHY
#include "cy_ethif.h"
#include "cy_sysint.h"
#include <string.h>
#include "cedi.h"

#define ARM_ETH_MAC_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(0,1) /* driver version */



/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
  ARM_ETH_MAC_API_VERSION,
  ARM_ETH_MAC_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_ETH_MAC_CAPABILITIES DriverCapabilities = {
  0U,                        /* checksum_offload_rx_ip4  */
  0U,                        /* checksum_offload_rx_ip6  */
  0U,                        /* checksum_offload_rx_udp  */
  0U,                        /* checksum_offload_rx_tcp  */
  0U,                        /* checksum_offload_rx_icmp */
  0U,                        /* checksum_offload_tx_ip4  */
  0U,                        /* checksum_offload_tx_ip6  */
  0U,                        /* checksum_offload_tx_udp  */
  0U,                        /* checksum_offload_tx_tcp  */
  0U,                        /* checksum_offload_tx_icmp */
  ARM_ETH_INTERFACE_RMII, /* media_interface          */
  0,                                                                /* mac_address              */
  1,                                                                /* event_rx_frame           */
  1,                                                                /* event_tx_frame           */
  1,                                                                /* event_wakeup             */
  0                                      /* precision_timer          */
} ;


#define ETH_REG_BASE ( ETH0 )


/* Local variables */
static EMAC_CTRL Emac;


static cy_stc_ethif_wrapper_config_t stcWrapperConfig =
{
  .stcInterfaceSel = CY_ETHIF_CTL_RMII_100,
  .bRefClockSource = CY_ETHIF_EXTERNAL_HSIO,
  .u8RefClkDiv = 1
} ;

/** General Ethernet configuration  */
static cy_stc_ethif_mac_config_t stcENETConfig = {
                .bintrEnable         = 1,                           /** Interrupt enable  */
                .dmaDataBurstLen     = CY_ETHIF_DMA_DBUR_LEN_4,
                .u8dmaCfgFlags       = CY_ETHIF_CFG_DMA_FRCE_TX_BRST,
                .mdcPclkDiv          = CY_ETHIF_MDC_DIV_BY_48,      /** source clock is 80 MHz and MDC must be less than 2.5MHz   */
                .u8rxLenErrDisc      = 0,                           /** Length error frame not discarded  */
                .u8disCopyPause      = 0,
                .u8chkSumOffEn       = 0,                           /** Checksum for both Tx and Rx disabled    */
                .u8rx1536ByteEn      = 1,                           /** Enable receive frame up to 1536    */
                .u8rxJumboFrEn       = 0,
                .u8enRxBadPreamble   = 1,
                .u8ignoreIpgRxEr     = 0,
                .u8storeUdpTcpOffset = 0,
                .u8aw2wMaxPipeline   = 2,                           /** Value must be > 0   */
                .u8ar2rMaxPipeline   = 2,                           /** Value must be > 0   */
                .u8pfcMultiQuantum   = 0,
                .pstcWrapperConfig   = &stcWrapperConfig,
                .pstcTSUConfig       = NULL, //&stcTSUConfig,               /** TSU settings    */
                .btxq0enable         = 1,                           /** Tx Q0 Enabled   */
                .btxq1enable         = 0,                           /** Tx Q1 Disabled  */
                .btxq2enable         = 0,                           /** Tx Q2 Disabled  */
                .brxq0enable         = 1,                           /** Rx Q0 Enabled   */
                .brxq1enable         = 0,                           /** Rx Q1 Disabled  */
                .brxq2enable         = 0,                           /** Rx Q2 Disabled  */
};

/** Interrupt configurations    */
static cy_stc_ethif_intr_config_t stcInterruptConfig = {
                .btsu_time_match        = 0,          /** Timestamp unit time match event */
                .bwol_rx                = 0,          /** Wake-on-LAN event received */
                .blpi_ch_rx             = 0,          /** LPI indication status bit change received */
                .btsu_sec_inc           = 0,          /** TSU seconds register increment */
                .bptp_tx_pdly_rsp       = 0,          /** PTP pdelay_resp frame transmitted */
                .bptp_tx_pdly_req       = 0,          /** PTP pdelay_req frame transmitted */
                .bptp_rx_pdly_rsp       = 0,          /** PTP pdelay_resp frame received */
                .bptp_rx_pdly_req       = 0,          /** PTP pdelay_req frame received */
                .bptp_tx_sync           = 0,          /** PTP sync frame transmitted */
                .bptp_tx_dly_req        = 0,          /** PTP delay_req frame transmitted */
                .bptp_rx_sync           = 0,          /** PTP sync frame received */
                .bptp_rx_dly_req        = 0,          /** PTP delay_req frame received */
                .bext_intr              = 0,          /** External input interrupt detected */
                .bpause_frame_tx        = 0,          /** Pause frame transmitted */
                .bpause_time_zero       = 0,          /** Pause time reaches zero or zero pause frame received */
                .bpause_nz_qu_rx        = 0,          /** Pause frame with non-zero quantum received */
                .bhresp_not_ok          = 0,          /** DMA HRESP not OK */
                .brx_overrun            = 0 /*1*/,          /** Rx overrun error */
                .bpcs_link_change_det   = 0,          /** Link status change detected by PCS */
                .btx_complete           = 1,          /** Frame has been transmitted successfully */
                .btx_fr_corrupt         = 1,          /** Tx frame corrupted */
                .btx_retry_ex_late_coll = 1,          /** Retry limit exceeded or late collision */
                .btx_underrun           = 1,          /** Tx underrun */
                .btx_used_read          = 0 /*1*/,          /** Used bit set has been read in Tx descriptor list */
                .brx_used_read          = 0 /*1*/,          /** Used bit set has been read in Rx descriptor list */
                .brx_complete           = 1,          /** Frame received successfully and stored */
                .bman_frame             = 0,          /** Management frame sent */
};


#define NUMRXPOOLBUFS ( CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE + ( CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE / 2 ) )
cy_ethif_buffpool_t RxBufPool ;
uint8_t RxPoolBufs[ NUMRXPOOLBUFS ][CY_ETH_SIZE_MAX_FRAME] __ALIGNED(8) ;
uint8_t RxPoolInPos = 0 ;
uint8_t RxPoolOutPos = 0 ;
uint8_t RxPoolBufCount = 0 ;

uint8_t TxPoolBuffers[ CY_ETH_DEFINE_TOTAL_BD_PER_TXQUEUE ][CY_ETH_SIZE_MAX_FRAME] __ALIGNED(8) ;
volatile uint32_t TxHeadPos = 0 ;
volatile uint32_t TxTailPos = 0 ;


struct RxFrameBuffer
{
  uint8_t Buffer[CY_ETH_SIZE_MAX_FRAME] ;
  uint32_t Length ;
} ;

#define NUMRXFRAMEBUFS ( NUMRXPOOLBUFS )
struct RxFrameBuffer RxFrameBufs[ NUMRXFRAMEBUFS ] ;
volatile uint32_t RxFrameHeadPos = 0 ;
volatile uint32_t RxFrameTailPos = 0 ;



void eth0_rxframecb(ETH_Type *base, uint8_t * rx_buffer, uint32_t length)
{
  struct RxFrameBuffer *RxFrameBuf ;
  uint8_t NextHeadPos ;
  
  NextHeadPos = RxFrameHeadPos + 1 ;
  if( NUMRXFRAMEBUFS <= NextHeadPos )
  {
    NextHeadPos = 0 ;
  }
  if( NextHeadPos != RxFrameTailPos )
  {
    RxFrameBuf = &RxFrameBufs[ RxFrameHeadPos ] ;
    memcpy( RxFrameBuf->Buffer, rx_buffer, length ) ;
    RxFrameBuf->Length = length ;
    if( NULL != Emac.cb_event )
    {
       Emac.cb_event( ARM_ETH_MAC_EVENT_RX_FRAME ) ;
    }
    RxFrameHeadPos = NextHeadPos ;
  }
  if( CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE > RxPoolBufCount )
  {  /* put rx buffer back in the pool */
    RxBufPool[ RxPoolInPos++ ] = rx_buffer ;
    if( CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE <= RxPoolInPos )
    {
      RxPoolInPos = 0 ;
    }
    RxPoolBufCount++ ;
  }
}

void eth0_rxgetbuff(ETH_Type *base, uint8_t **u8RxBuffer, uint32_t *u32Length)
{
  uint8_t *RxBuffer ;
  
  if( RxPoolBufCount )
  {
    RxBuffer = RxBufPool[ RxPoolOutPos ] ;
    RxBufPool[ RxPoolOutPos ] = NULL ;
    RxPoolOutPos++ ;
    *u8RxBuffer = RxBuffer ;
    *u32Length = CY_ETH_SIZE_MAX_FRAME ;
    if( CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE <= RxPoolOutPos )
    {
      RxPoolOutPos = 0 ;
    }
    RxPoolBufCount-- ;
  }
}

void eth0_txcompletecb( ETH_Type *base, uint8_t u8QueueIndex)
{
  if( TxHeadPos != TxTailPos )
  {
    if( NULL != Emac.cb_event )
    {
       Emac.cb_event( ARM_ETH_MAC_EVENT_TX_FRAME ) ;
    }
    TxTailPos = TxTailPos + 1 ;
    if( CY_ETH_DEFINE_TOTAL_BD_PER_TXQUEUE <= TxTailPos )
    {
      TxTailPos = 0 ;
    }
  }
}


static cy_stc_ethif_cb_t stcInterruptCB = {
    /** Callback functions  */
                .rxframecb  = eth0_rxframecb, //Ethx_RxFrameCB,
                .txerrorcb  = NULL,
                .txcompletecb = eth0_txcompletecb, /** Set it to NULL if callback is not required */
                .tsuSecondInccb = NULL,
                .rxgetbuff = eth0_rxgetbuff
};

static const cy_stc_sysint_t irq_cfg_ethx_q0 = {.intrSrc  = ((NvicMux3_IRQn << 16) | eth_0_interrupt_eth_0_IRQn), .intrPriority=1UL};
static const cy_stc_sysint_t irq_cfg_ethx_q1 = {.intrSrc  = ((NvicMux3_IRQn << 16) | eth_0_interrupt_eth_1_IRQn), .intrPriority=1UL};
static const cy_stc_sysint_t irq_cfg_ethx_q2 = {.intrSrc  = ((NvicMux3_IRQn << 16) | eth_0_interrupt_eth_2_IRQn), .intrPriority=1UL};


static void Cy_Ethx_InterruptHandler (void)
{
    Cy_ETHIF_DecodeEvent(ETH_REG_BASE);
}







static ARM_DRIVER_VERSION GetVersion (void) {
  return DriverVersion;
}

static ARM_ETH_MAC_CAPABILITIES GetCapabilities (void) {
  return DriverCapabilities;
}

static int32_t Initialize (ARM_ETH_MAC_SignalEvent_t cb_event) {

  for( uint32_t rxBufIdx = 0 ; rxBufIdx < CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE ; rxBufIdx++ )
  {  /* put initial buffers in the pool */
    RxBufPool[ rxBufIdx ] = RxPoolBufs[ rxBufIdx ] ;
  }
    
  /* Clear control structure */
  memset ((void *)&Emac, 0, sizeof (EMAC_CTRL));
  
  Emac.cb_event = cb_event;
  Emac.flags    = EMAC_FLAG_INIT;

  return ARM_DRIVER_OK;
}

static int32_t Uninitialize (void) {
  return ARM_DRIVER_OK;
}

static int32_t PowerControl (ARM_POWER_STATE state) {
  cy_en_ethif_status_t    eth_status;
  uint32_t Count ;
  
  switch (state)
  {
    case ARM_POWER_OFF:
      return ARM_DRIVER_ERROR_UNSUPPORTED;
    case ARM_POWER_LOW:
      return ARM_DRIVER_ERROR_UNSUPPORTED;
    case ARM_POWER_FULL:
      Cy_SysInt_Init(&irq_cfg_ethx_q0, Cy_Ethx_InterruptHandler);
      Cy_SysInt_Init(&irq_cfg_ethx_q1, Cy_Ethx_InterruptHandler);
      Cy_SysInt_Init(&irq_cfg_ethx_q2, Cy_Ethx_InterruptHandler);

      stcENETConfig.pRxQbuffPool[ 0 ] = &RxBufPool ;
      stcENETConfig.pRxQbuffPool[ 1 ] = NULL ;
      eth_status = Cy_ETHIF_Init(ETH0, &stcENETConfig, &stcInterruptConfig);
      if (CY_ETHIF_SUCCESS != eth_status)
      {
        return ARM_DRIVER_ERROR ;
      }
      Cy_ETHIF_RegisterCallbacks(ETH0, &stcInterruptCB);
      for( uint32_t rxBufIdx = 0 ; rxBufIdx < CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE ; rxBufIdx++ )
      {  /* these buffers are in use */
        RxBufPool[ rxBufIdx ] = NULL ;
      }
      for( uint32_t rxBufIdx = 0 ; rxBufIdx < ( NUMRXPOOLBUFS - CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE ) ; rxBufIdx++ )
      {  /* put remaining buffers in the pool */
        RxBufPool[ rxBufIdx ] = RxPoolBufs[ CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE + rxBufIdx ] ;
        RxPoolInPos++ ;
        RxPoolBufCount++ ;
      }
      NVIC_EnableIRQ(NvicMux3_IRQn);

      break ;
    default:
      return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  return ARM_DRIVER_OK;
}

static int32_t GetMacAddress (ARM_ETH_MAC_ADDR *ptr_addr) {
  return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t SetMacAddress (const ARM_ETH_MAC_ADDR *ptr_addr) {

    cy_stc_ethif_filter_config_t dstMacFilter =
    {
        .typeFilter = CY_ETHIF_FILTER_TYPE_DESTINATION,
        .filterAddr.byte[ 0 ] = ptr_addr->b[ 0 ],
        .filterAddr.byte[ 1 ] = ptr_addr->b[ 1 ],
        .filterAddr.byte[ 2 ] = ptr_addr->b[ 2 ],
        .filterAddr.byte[ 3 ] = ptr_addr->b[ 3 ],
        .filterAddr.byte[ 4 ] = ptr_addr->b[ 4 ],
        .filterAddr.byte[ 5 ] = ptr_addr->b[ 5 ],
        .ignoreBytes = 0x00,
    };
    if( CY_ETHIF_SUCCESS != Cy_ETHIF_SetFilterAddress( ETH0, CY_ETHIF_FILTER_NUM_1, &dstMacFilter ) )
    {
      return ARM_DRIVER_ERROR ;
    }
    
    return ARM_DRIVER_OK;
}

static int32_t SetAddressFilter (const ARM_ETH_MAC_ADDR *ptr_addr, uint32_t num_addr) {
  return ARM_DRIVER_OK;
}

static int32_t SendFrame (const uint8_t *frame, uint32_t len, uint32_t flags) {

  uint8_t *TxBuffer ;
  int32_t RetVal ;
  uint32_t NextHead ;
  
  NextHead = TxHeadPos + 1 ;
  if( CY_ETH_DEFINE_TOTAL_BD_PER_TXQUEUE <= NextHead )
  {
    NextHead = 0 ;
  }
  if( NextHead != TxTailPos )
  {
    TxBuffer = TxPoolBuffers[ TxHeadPos ] ;
    memcpy( TxBuffer, frame, len ) ;
    if( CY_ETHIF_SUCCESS == Cy_ETHIF_TransmitFrame( ETH0, TxBuffer, len, CY_ETH_QS0_0, 1 ) )
    {
      RetVal = ARM_DRIVER_OK ;
    }
    TxHeadPos = NextHead ;
  }
  else
  {
    RetVal = ARM_DRIVER_ERROR_BUSY ;
  }

  return ( RetVal );
}

static int32_t ReadFrame (uint8_t *frame, uint32_t len) {
  struct RxFrameBuffer *RxFrameBuf ;
  uint32_t RetVal ;
  
  RetVal = 0 ;
  if( RxFrameHeadPos != RxFrameTailPos )
  {
    RxFrameBuf = &RxFrameBufs[ RxFrameTailPos ] ;
    if( ( NULL != frame ) && ( RxFrameBuf->Length <= len ) )
    {
      memcpy( frame, RxFrameBuf->Buffer, RxFrameBuf->Length ) ;
      RetVal = RxFrameBuf->Length ;
      RxFrameBuf->Length = 0 ;
    }
    RxFrameBuf->Length = 0 ;
    RxFrameTailPos = RxFrameTailPos + 1 ;
    if( NUMRXFRAMEBUFS <= RxFrameTailPos )
    {
      RxFrameTailPos = 0 ;
    }
  }
  return ( RetVal );
}

static uint32_t GetRxFrameSize (void) {
  uint32_t RetVal ;
  
  RetVal = 0 ;
  if( RxFrameHeadPos != RxFrameTailPos )
  {
    RetVal = RxFrameBufs[ RxFrameTailPos ].Length ;
  }
  return( RetVal ) ;
}

static int32_t GetRxFrameTime (ARM_ETH_MAC_TIME *time) {
  (void)time;

  return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t GetTxFrameTime (ARM_ETH_MAC_TIME *time) {
  (void)time;

  return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ControlTimer (uint32_t control, ARM_ETH_MAC_TIME *time) {
  (void)time;
  (void)control;

  return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t Control (uint32_t control, uint32_t arg) {
  return ARM_DRIVER_OK;
}

static int32_t PHY_Read (uint8_t phy_addr, uint8_t reg_addr, uint16_t *data) {
  
  *data = Cy_ETHIF_PhyRegRead( ETH0, reg_addr, phy_addr ) ;
  
  return ARM_DRIVER_OK;
}

static int32_t PHY_Write (uint8_t phy_addr, uint8_t reg_addr, uint16_t data) {
  
  Cy_ETHIF_PhyRegWrite( ETH0, reg_addr, data, phy_addr ) ;
  
  return ARM_DRIVER_OK;
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
