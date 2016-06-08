/*
 * FreeModbus Libary: Microsemi SmartFusion2 Port
 * Copyright (C) 2013 Microsemi Corporation <soc_tech@microsemi.com>
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
 * File: $Id: portother.c 15146 2011-03-11 11:37:07Z tommy.murphy $
 */

/* ----------------------- Platform includes --------------------------------*/
/* SmartFusion2 MSS CMSIS header */
//#include "m2sxxx.h"

/* ----------------------- Modbus includes ----------------------------------*/
//#include "mb.h"

/* ----------------------- Variables ----------------------------------------*/
//static ULONG ulNesting = 0;

/* ----------------------- Start implementation -----------------------------*/
//void
//vMBPortEnterCritical( void )
//{
//	assert( ulNesting < ((ULONG)~0) );
///	( void )__disable_irq(  );
//    ulNesting++;
//}

void
vMBPortExitCritical( void )
{
	assert( ulNesting > 0 );
    ulNesting--;
    if( 0 == ulNesting )
   {
    	( void )__enable_irq(  );
    }
}
