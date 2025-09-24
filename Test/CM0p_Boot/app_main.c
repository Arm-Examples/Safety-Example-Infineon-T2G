#include <stdlib.h>
#include <stdio.h>
#include "RTE_Components.h"             // Component selection
#include CMSIS_device_header            // Device header
#include "main.h"
#include "cy_pdl.h"
#include "cybsp.h"
#include "cmsis_vio.h"

extern int retarget_stdio_init (void);


/*
  Start Cortex-M7 core 0
*/
void start_CM7_0 (void) {
  uint32_t value;
  
  CPUSS->CM7_0_VECTOR_TABLE_BASE = BASE_CODE_FLASH_CM7_0;
  CPUSS->CM7_0_PWR_CTL = (0x05FA << CPUSS_UDB_PWR_CTL_VECTKEYSTAT_Pos) | (3 << CPUSS_UDB_PWR_CTL_PWR_MODE_Pos) ;
  value = CPUSS->CM7_0_CTL;
  CPUSS->CM7_0_CTL = (value & ~(CPUSS_CM7_0_CTL_CPU_WAIT_Msk));
  value = SRSS->CLK_ROOT_SELECT[1];
  SRSS->CLK_ROOT_SELECT[1] = (value | (1 << SRSS_CLK_ROOT_SELECT_ENABLE_Pos));
}

/*
  Start Cortex-M7 core 1
*/
void start_CM7_1 (void) {
  uint32_t value;
  
  CPUSS->CM7_1_VECTOR_TABLE_BASE = BASE_CODE_FLASH_CM7_1;
  CPUSS->CM7_1_PWR_CTL = (0x05FA << CPUSS_UDB_PWR_CTL_VECTKEYSTAT_Pos) | (3 << CPUSS_UDB_PWR_CTL_PWR_MODE_Pos);
  value = CPUSS->CM7_1_CTL;
  CPUSS->CM7_1_CTL = (value & ~(CPUSS_CM7_1_CTL_CPU_WAIT_Msk));
  value = SRSS->CLK_ROOT_SELECT[1];
  SRSS->CLK_ROOT_SELECT[1] = (value | (1 << SRSS_CLK_ROOT_SELECT_ENABLE_Pos));
}

/*
  Application initialization.
*/
int app_main (void) {

  init_cycfg_all();                     // System initialization

  vioInit();                            // Initialize Virtual I/O
  retarget_stdio_init();                // Initialize UART for STDIO

  printf("CM0+ running ...\n");

  start_CM7_0( ) ;
  printf("CM7 Core 0 running ...\n");

  start_CM7_1( ) ;
  printf("CM7 Core 1 running ...\n");

  // Cortex-M0+ code continues execution after both Cortex-M7 cores are started
  for (;;) {
//  Cy_GPIO_Inv( LED1_PORT, LED1_PIN ) ;
    for (uint32_t count = 0U; count < 1000000U; count++ ) {
      __NOP();
    }
  }

  return 0;
}
