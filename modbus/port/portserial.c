/*
 * FreeModbus Libary: Microsemi SmartFusion2 Port
 * Copyright (C) 2013 Microsemi Corporation <soc_tech@microsemi.com>
 *
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * IF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * SVN $Revision: 15146 $
 * SVN $Date: 2011-03-11 11:37:07 +0000 (Fri, 11 Mar 2011) $
 * File: $Id: portserial.c 15146 2011-03-11 11:37:07Z tommy.murphy $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"
#include "uart_gsc3280.h"
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
/* ----------------------- Defines ------------------------------------------*/

#define MB_UART UART3

/* ----------------------- Start implementation -----------------------------*/
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    uart_enable_irq(MB_UART, xTxEnable, xRxEnable);
}

void
vMBPortClose( void )
{

}


BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
    ucPORT = ucPORT;
    ucDataBits = ucDataBits;
    eParity = eParity;

    uart_init(MB_UART, ulBaudRate);
	
	return TRUE;
}

BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
    uart_putc(MB_UART, (unsigned char)ucByte);

	return TRUE;

}

BOOL 
xMBPortSerialGetByte( CHAR* pucByte )
{
    *pucByte = uart_getc(MB_UART);

	return TRUE;
	
}

/* Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
void prvvUARTTxReadyISR( void )
{
    pxMBFrameCBTransmitterEmpty(  );
}

/* Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
void prvvUARTRxISR( void )
{
    pxMBFrameCBByteReceived(  );
}

void ENTER_CRITICAL_SECTION()
{

}

void EXIT_CRITICAL_SECTION()
{

}

void uart_mb_irq_handle(void *arg)
{
    volatile unsigned char lsr = *(volatile unsigned char *)(MB_UART + IIR);

    if ((lsr == UART_IIR_RDA) || (lsr == UART_IIR_TIMEOUT))
    {
        prvvUARTRxISR();
    }
    else if (lsr == UART_IIR_THRE)
    {
        prvvUARTTxReadyISR();
    }
}


