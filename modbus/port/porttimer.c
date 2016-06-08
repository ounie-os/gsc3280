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
 * File: $Id: porttimer.c 15146 2011-03-11 11:37:07Z tommy.murphy $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"
#include "string.h"
#include "timer_gsc3280.h"
#include "gpio_gsc3280.h"
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"

/* ----------------------- Static variables ---------------------------------*/
ULONG ClockValue = 0;
ULONG tim_Clock=0;

static u8 flag = 0;


#define RX_DETECT_TIMER TIMER0

/* ----------------------- Start implementation -----------------------------*/

void vMBPortTimersEnable(  )
{
    timer_start(RX_DETECT_TIMER);
}

void vMBPortTimersDisable(  )
{
    timer_stop(RX_DETECT_TIMER);
}

/* Create an ISR which is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */
void prvvTIMERExpiredISR(void)
{
	(void) pxMBPortCBTimerExpired();
}

BOOL
xMBPortTimersInit( USHORT usTimeOut50us )
{
    ULONG period_us = usTimeOut50us * 50;
    timer_init(RX_DETECT_TIMER, prvvTIMERExpiredISR);
	timer_config(RX_DETECT_TIMER, period_us);
	return TRUE;
}

