#include "main.h"

#include "RTE_Components.h"
#include  CMSIS_device_header

extern int app_main (void);

int main (void) {

  __enable_irq();

  return app_main();
}
