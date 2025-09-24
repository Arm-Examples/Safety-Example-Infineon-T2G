// Copyright (c) 2024 Infineon Technologies AG. All rights reserved
// Licensed under the Apache License, Version 2.0, see APACHE_LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include "cybsp.h"

static cy_stc_scb_uart_context_t uartContext;

/**
  Initialize stdout
 
  \return          0 on success, or -1 on error.
*/
int retarget_stdio_init (void)
{
    if (Cy_SCB_UART_Init(scb_0_HW, &scb_0_config, &uartContext) == CY_SCB_UART_SUCCESS)
    {
        Cy_SCB_UART_Enable(scb_0_HW);
        return (0);
    }
    else
    {
        return (-1);
    }
}
 
/**
  Put a character to the stderr
 
  \param[in]   ch  Character to output
  \return          The character written, or -1 on write error.
*/
int stderr_putchar (int ch)
{
    while (Cy_SCB_UART_Put(scb_0_HW, ch) == 0);
    return (ch);
}

/**
  Put a character to the stdout
 
  \param[in]   ch  Character to output
  \return          The character written, or -1 on write error.
*/
int stdout_putchar (int ch)
{
    while (Cy_SCB_UART_Put(scb_0_HW, ch) == 0);
    return (ch);
}

/**
  Get a character from the stdio
 
  \return     The next character from the input, or -1 on read error.
*/
int stdin_getchar (void)
{
    uint32_t ret;

    do
    {
        ret = Cy_SCB_UART_Get(scb_0_HW);
    }
    while (ret == CY_SCB_UART_RX_NO_DATA);

    return (ret);
}