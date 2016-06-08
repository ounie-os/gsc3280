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
 * File: $Id: port.h 15146 2011-03-11 11:37:07Z tommy.murphy $
 */

#ifndef _PORT_H
#define _PORT_H

/* ----------------------- Platform includes --------------------------------*/

/* ----------------------- Defines ------------------------------------------*/

/* Use CMSIS ASSERT() rather than standard lib (newlib) assert() to avoid code
 * bloat due to linking of *printf() etc. support.
 */
#define assert

#define	    INLINE                      inline
#define    PR_BEGIN_EXTERN_C           extern "C" {
#define 	PR_END_EXTERN_C             }

extern void ENTER_CRITICAL_SECTION(void);    /* 关中断*/
extern void EXIT_CRITICAL_SECTION(void);     /* 开中断*/

typedef unsigned char BOOL;

typedef unsigned char UCHAR;
typedef char CHAR;

typedef unsigned short USHORT;
typedef short SHORT;

typedef unsigned int ULONG;
typedef int LONG;

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

/* ----------------------- Prototypes ---------------------------------------*/
//void vMBPortEnterCritical( void );
//void vMBPortExitCritical( void );

void uart_mb_irq_handle(void *arg);


#endif
