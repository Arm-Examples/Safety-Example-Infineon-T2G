/*---------------------------------------------------------------------------
 * Copyright (c) 2020-2025 Arm Limited (or its affiliates).
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
 *---------------------------------------------------------------------------*/

#include "Communication.h"

#include <string.h>

#include "system_defs.h"
#include "zones.h"
#include "cmsis_os2.h"
#include "rl_net.h"

/* Local variables located in shared RAM */
static uint32_t         sensor_val         __attribute__((section("ram_shared"))) = 0U;
static uint32_t         status_val         __attribute__((section("ram_shared"))) = 0U;
static uint32_t         operating_mode     __attribute__((section("ram_shared"))) = 0U;
static char             fault_info[512]    __attribute__((section("ram_shared")));
static osEventFlagsId_t fault_inject_event __attribute__((section("ram_shared"))) = NULL;

/* Thread stack located in RAM_COM */
static uint64_t communication_init_thread_stack[4096/8];

/* fault_inject_event event flags attributes */
static const osEventFlagsAttr_t fault_inject_event_attr = {
  .name       = "fault_inject_event",
  .attr_bits  = osSafetyClass(0U), 
  .cb_mem     = NULL,                                   /* System allocated control block */
  .cb_size    = 0U
};

/* CommunicationInitThread thread attributes */
static const osThreadAttr_t communication_init_thread_attr = {
  .name       = "CommunicationInitThread",
  .attr_bits  = osThreadUnprivileged                     | 
                osThreadZone(ZONE_COM)                   | 
                osSafetyClass(SAFETY_CLASS_COMMUNICATION), 
  .cb_mem     = NULL,                                   /* System allocated control block */
  .cb_size    = 0U,
  .stack_mem  = communication_init_thread_stack,        /* User allocated stack */
  .stack_size = sizeof(communication_init_thread_stack),
  .priority   = osPriorityNormal,
  .tz_module  = 0U,                                     /* Not used */
  .affinity_mask = 0U                                   /* Not used */
};

/* CommunicationInitThread thread:
   Start HTTP Web Server. 
   Handle also injection of a memory fault in the Communication thread. */
static __NO_RETURN void CommunicationInitThread (void *argument) {
  volatile uint32_t val;

  (void)argument;

  (void)netInitialize();                /* Initialize network stack (web server) */

  for (;;) {
    if (FaultWasInjected(FAULT_INJECT_SC1_MEM_ACCESS) != 0U) {
      /* If injection of a memory fault was activated from the web interface */
      val = *((uint32_t *)0x20000000);  /* Access memory out of Zone */
    }
    (void)osDelay(100U);
  }
}

/* Initialize CommunicationInitThread thread: 
   Communication threads must be started when RTOS is running 
   (from CommunicationInitThread thread) because 
   they use RTOS objects (mutex and semaphore) */
void CommunicationInit (void) {

  fault_inject_event = osEventFlagsNew(&fault_inject_event_attr);
  (void)osThreadNew(CommunicationInitThread, NULL, &communication_init_thread_attr);
}

/* Set operating mode for display (on the web page) */
void DisplaySetOperatingMode (uint32_t mode) {

  operating_mode = mode;
}

/* Get operating mode for display (when requested by a web page refresh) */
uint32_t DisplayGetOperatingMode (void) {

  return operating_mode;
}

/* Set status of the traffic lights for display (on the web page) */
void DisplaySetLightsStatus (uint32_t status) {

  status_val = status;
}

/* Get status of the traffic lights (when requested by a web page refresh) */
uint32_t DisplayGetLightsStatus (void) {

  return status_val;
}

/* Set traffic sensor value for display (on the web page) */
void DisplaySetSensorValue (uint32_t value) {

  sensor_val = value;
}

/* Get traffic sensor value for display (when requested by a web page refresh) */
uint32_t DisplayGetSensorValue (void) {

  return sensor_val;
}

/* Set Fault Info for display (on the web page) */
void DisplaySetFaultInfo (const char *str) {

  if (sizeof(fault_info) > (strlen(fault_info) + strlen(str))) {
    (void)strncat(fault_info, str, strlen(str));
  }
}

/* Get Fault Info for display (when requested by a web page refresh) */
const char *DisplayGetFaultInfo (void) {

  return ((const char *)fault_info);
}

/* Inject fault */
void FaultInject (uint32_t fault_flag) {

  (void)osEventFlagsSet(fault_inject_event, fault_flag);
}

/* Check if a fault was injected (through a web interface) */
uint32_t FaultWasInjected (uint32_t fault_flag) {
  uint32_t flags, ret;

  flags = osEventFlagsWait(fault_inject_event, fault_flag, osFlagsWaitAny, 0U);
  if ((flags & 0x80000000U) != 0U) {
    // Ignore error flags
    flags = 0U;
  }
  if ((flags & fault_flag) != 0U) {
    ret = 1U;
  } else {
    ret = 0U;
  }

  return ret;
}
