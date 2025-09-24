/******************************************************************************
 * @file     vio_KIT_T2G-B-H_LITE.c
 * @brief    Virtual I/O implementation for Infineon KIT_T2G-B-H_LITE board
 * @version  V1.0.0
 * @date     10. September 2025
 ******************************************************************************/
/*
 * Copyright (c) 2025 Arm Limited (or its affiliates).
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
 */

/*! \page KIT_T2G-B-H_LITE Physical I/O Mapping

The table below lists the physical I/O mapping of this CMSIS-Driver VIO implementation.

| Virtual I/O   | Variable       | Board component    | Pin
|:--------------|:---------------|:-------------------|:------
| vioBUTTON0    | vioSignalIn.0  | USER BUTTON1 (SW3) | P5[3]
| vioBUTTON1    | vioSignalIn.1  | USER BUTTON2 (SW4) | P17[0]
| vioLED0       | vioSignalOut.0 | USER LED1 (LED3)   | P5[0]
| vioLED1       | vioSignalOut.1 | USER LED2 (LED4)   | P5[1]
| vioLED2       | vioSignalOut.2 | USER LED3 (LED5)   | P5[2]
*/

#include "cmsis_vio.h"

#include "RTE_Components.h"                     // Component selection
#include CMSIS_device_header

#if !defined CMSIS_VOUT || !defined CMSIS_VIN
#include "cy_pdl.h"
#include "cybsp.h"
#endif

// VIO input, output definitions
#ifndef VIO_VALUE_NUM
#define VIO_VALUE_NUM           5U              // Number of values
#endif

// VIO input, output variables
static uint32_t vioSignalIn             __USED; // Memory for incoming signal
static uint32_t vioSignalOut            __USED; // Memory for outgoing signal
static int32_t  vioValue[VIO_VALUE_NUM] __USED; // Memory for value used in vioGetValue/vioSetValue

#if !defined CMSIS_VOUT || !defined CMSIS_VIN

// VIO Active State
#define VIO_ACTIVE_LOW          0U
#define VIO_ACTIVE_HIGH         1U

typedef struct {
  uint32_t       vio_signal;
  GPIO_PRT_Type *port_base;
  uint32_t       pin_num;
  uint32_t       active_state;
} pin_config_t;

#if !defined CMSIS_VOUT
// Physical output pins
static const pin_config_t pin_config_output[] = {
//  vio_signal, port_base,            pin_num,             active_state
  { vioLED0,    LED1_PORT,            LED1_PIN,            VIO_ACTIVE_LOW },
  { vioLED1,    LED2_PORT,            LED2_PIN,            VIO_ACTIVE_LOW },
  { vioLED2,    LED3_PORT,            LED3_PIN,            VIO_ACTIVE_LOW }
};
#endif

#if !defined CMSIS_VIN
// Physical input pins
static const pin_config_t pin_config_input[] = {
//  vio_signal, port_base,            pin_num,             active_state
  { vioBUTTON0, CYBSP_USER_BTN1_PORT, CYBSP_USER_BTN1_PIN, VIO_ACTIVE_LOW },
  { vioBUTTON1, CYBSP_USER_BTN2_PORT, CYBSP_USER_BTN2_PIN, VIO_ACTIVE_LOW }
};

#endif
#endif

// Initialize test input, output.
void vioInit (void) {
  uint32_t n;

  vioSignalIn  = 0U;
  vioSignalOut = 0U;

  for (n = 0U; n < VIO_VALUE_NUM; n++) {
    vioValue[n] = 0U;
  }

#if !defined CMSIS_VOUT
// The CM0+ initializes the output pins during setup, as specified in the Device Configurator
#endif

#if !defined CMSIS_VIN
// The CM0+ initializes the input pins during setup, as specified in the Device Configurator
#endif
}

// Set signal output.
void vioSetSignal (uint32_t mask, uint32_t signal) {
#if !defined CMSIS_VOUT
  uint32_t pin_value;
  uint8_t  n;
#endif

  vioSignalOut &= ~mask;
  vioSignalOut |=  mask & signal;

#if !defined CMSIS_VOUT
  // Output signals to LEDs
  for (n = 0U; n < (sizeof(pin_config_output) / sizeof(pin_config_t)); n++) {
    if ((mask & pin_config_output[n].vio_signal) != 0U) {
      if ((signal & pin_config_output[n].vio_signal) != 0U) {
        pin_value = 1U;
      } else {
        pin_value = 0U;
      }
      if (pin_value == pin_config_output[n].active_state) {
        Cy_GPIO_Set(pin_config_output[n].port_base, pin_config_output[n].pin_num);
      } else {
        Cy_GPIO_Clr(pin_config_output[n].port_base, pin_config_output[n].pin_num);
      }
    }
  }
#endif
}

// Get signal input.
uint32_t vioGetSignal (uint32_t mask) {
  uint32_t signal;
#if !defined CMSIS_VIN
  uint32_t pin_value;
  uint8_t  n;
#endif

#if !defined CMSIS_VIN
  // Get input signals from buttons
  for (n = 0U; n < (sizeof(pin_config_input) / sizeof(pin_config_t)); n++) {
    if ((mask & pin_config_input[n].vio_signal) != 0U) {
      pin_value = Cy_GPIO_Read(pin_config_input[n].port_base, pin_config_input[n].pin_num);
      if (pin_value == pin_config_input[n].active_state) {
        vioSignalIn |=  pin_config_input[n].vio_signal;
      } else {
        vioSignalIn &= ~pin_config_input[n].vio_signal;
      }
    }
  }
#endif

  signal = vioSignalIn & mask;

  return signal;
}

// Set value output.
void vioSetValue (uint32_t id, int32_t value) {
  uint32_t index = id;
#if !defined CMSIS_VOUT
// Add user variables here:

#endif

  if (index >= VIO_VALUE_NUM) {
    return;                             /* return in case of out-of-range index */
  }

  vioValue[index] = value;

#if !defined CMSIS_VOUT
// Add user code here:

#endif
}

// Get value input.
int32_t vioGetValue (uint32_t id) {
  uint32_t index = id;
  int32_t  value;
#if !defined CMSIS_VIN
// Add user variables here:

#endif

  if (index >= VIO_VALUE_NUM) {
    return 0U;                          /* return 0 in case of out-of-range index */
  }

#if !defined CMSIS_VIN
// Add user code here:

#endif

  value = vioValue[index];

  return value;
}