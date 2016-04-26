/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1985 MIPS Computer Systems, Inc.
 * Copyright (C) 1994, 95, 99, 2003 by Ralf Baechle
 * Copyright (C) 1990 - 1992, 1999 Silicon Graphics, Inc.
 */
#ifndef _ASM_REGDEF_H
#define _ASM_REGDEF_H


//#if _MIPS_SIM == _MIPS_SIM_ABI32
#if 1 

/*
 * Symbolic register names for 32 bit ABI
 */
#define zero	$0	/* wired zero */
#define AT	$1	/* assembler temp  - uppercase because of ".set at" */
#define v0	$2	/* return value */
#define v1	$3
#define a0	$4	/* argument registers */
#define a1	$5
#define a2	$6
#define a3	$7
#define t0	$8	/* caller saved */
#define t1	$9
#define t2	$10
#define t3	$11
#define t4	$12
#define t5	$13
#define t6	$14
#define t7	$15
#define s0	$16	/* callee saved */
#define s1	$17
#define s2	$18
#define s3	$19
#define s4	$20
#define s5	$21
#define s6	$22
#define s7	$23
#define t8	$24	/* caller saved */
#define t9	$25
#define jp	$25	/* PIC jump register */
#define k0	$26	/* kernel scratch */
#define k1	$27
#define gp	$28	/* global pointer */
#define sp	$29	/* stack pointer */
#define fp	$30	/* frame pointer */
#define s8	$30	/* same like fp! */
#define ra	$31	/* return address */

#endif /* _MIPS_SIM == _MIPS_SIM_ABI32 */

//#if _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32
#if  0
#define zero	$0	/* wired zero */
#define AT	$at	/* assembler temp - uppercase because of ".set at" */
#define v0	$2	/* return value - caller saved */
#define v1	$3
#define a0	$4	/* argument registers */
#define a1	$5
#define a2	$6
#define a3	$7
#define a4	$8	/* arg reg 64 bit; caller saved in 32 bit */
#define ta0	$8
#define a5	$9
#define ta1	$9
#define a6	$10
#define ta2	$10
#define a7	$11
#define ta3	$11
#define t0	$12	/* caller saved */
#define t1	$13
#define t2	$14
#define t3	$15
#define s0	$16	/* callee saved */
#define s1	$17
#define s2	$18
#define s3	$19
#define s4	$20
#define s5	$21
#define s6	$22
#define s7	$23
#define t8	$24	/* caller saved */
#define t9	$25	/* callee address for PIC/temp */
#define jp	$25	/* PIC jump register */
#define k0	$26	/* kernel temporary */
#define k1	$27
#define gp	$28	/* global pointer - caller saved for PIC */
#define sp	$29	/* stack pointer */
#define fp	$30	/* frame pointer */
#define s8	$30	/* callee saved */
#define ra	$31	/* return address */

#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32 */

/*
 * Coprocessor 0 register names
 */
#define CP0_INDEX $0
#define CP0_RANDOM $1
#define CP0_ENTRYLO0 $2
#define CP0_ENTRYLO1 $3
#define CP0_CONF $3
#define CP0_CONTEXT $4
#define CP0_PAGEMASK $5
#define CP0_WIRED $6
#define CP0_INFO $7
#define CP0_BADVADDR $8
#define CP0_COUNT $9
#define CP0_ENTRYHI $10
#define CP0_COMPARE $11
#define CP0_STATUS $12
#define CP0_CAUSE $13
#define CP0_EPC $14
#define CP0_PRID $15
#define CP0_CONFIG $16
#define CP0_LLADDR $17
#define CP0_WATCHLO $18
#define CP0_WATCHHI $19
#define CP0_XCONTEXT $20
#define CP0_FRAMEMASK $21
#define CP0_DIAGNOSTIC $22
#define CP0_DEBUG $23
#define CP0_DEPC $24
#define CP0_PERFORMANCE $25
#define CP0_ECC $26
#define CP0_CACHEERR $27
#define CP0_TAGLO $28
#define CP0_TAGHI $29
#define CP0_ERROREPC $30
#define CP0_DESAVE $31

/*
 * Status register bits available in all MIPS CPUs.
 */
#define ST0_IM			0x0000ff00
#define  STATUSB_IP0		8
#define  STATUSF_IP0		(_ULCAST_(1) <<  8)
#define  STATUSB_IP1		9
#define  STATUSF_IP1		(_ULCAST_(1) <<  9)
#define  STATUSB_IP2		10
#define  STATUSF_IP2		(_ULCAST_(1) << 10)
#define  STATUSB_IP3		11
#define  STATUSF_IP3		(_ULCAST_(1) << 11)
#define  STATUSB_IP4		12
#define  STATUSF_IP4		(_ULCAST_(1) << 12)
#define  STATUSB_IP5		13
#define  STATUSF_IP5		(_ULCAST_(1) << 13)
#define  STATUSB_IP6		14
#define  STATUSF_IP6		(_ULCAST_(1) << 14)
#define  STATUSB_IP7		15
#define  STATUSF_IP7		(_ULCAST_(1) << 15)
#define  STATUSB_IP8		0
#define  STATUSF_IP8		(_ULCAST_(1) <<  0)
#define  STATUSB_IP9		1
#define  STATUSF_IP9		(_ULCAST_(1) <<  1)
#define  STATUSB_IP10		2
#define  STATUSF_IP10		(_ULCAST_(1) <<  2)
#define  STATUSB_IP11		3
#define  STATUSF_IP11		(_ULCAST_(1) <<  3)
#define  STATUSB_IP12		4
#define  STATUSF_IP12		(_ULCAST_(1) <<  4)
#define  STATUSB_IP13		5
#define  STATUSF_IP13		(_ULCAST_(1) <<  5)
#define  STATUSB_IP14		6
#define  STATUSF_IP14		(_ULCAST_(1) <<  6)
#define  STATUSB_IP15		7
#define  STATUSF_IP15		(_ULCAST_(1) <<  7)
#define ST0_CH			0x00040000
#define ST0_SR			0x00100000
#define ST0_TS			0x00200000
#define ST0_BEV			0x00400000
#define ST0_RE			0x02000000
#define ST0_FR			0x04000000
#define ST0_CU			0xf0000000
#define ST0_CU0			0x10000000
#define ST0_CU1			0x20000000
#define ST0_CU2			0x40000000
#define ST0_CU3			0x80000000
#define ST0_XX			0x80000000	/* MIPS IV naming */

/*
 * Bitfields and bit numbers in the coprocessor 0 cause register.
 *
 * Refer to your MIPS R4xx0 manual, chapter 5 for explanation.
 */
#define  CAUSEB_EXCCODE		2
#define  CAUSEF_EXCCODE		(_ULCAST_(31)  <<  2)
#define  CAUSEB_IP		8
#define  CAUSEF_IP		(_ULCAST_(255) <<  8)
#define  CAUSEB_IP0		8
#define  CAUSEF_IP0		(_ULCAST_(1)   <<  8)
#define  CAUSEB_IP1		9
#define  CAUSEF_IP1		(_ULCAST_(1)   <<  9)
#define  CAUSEB_IP2		10
#define  CAUSEF_IP2		(_ULCAST_(1)   << 10)
#define  CAUSEB_IP3		11
#define  CAUSEF_IP3		(_ULCAST_(1)   << 11)
#define  CAUSEB_IP4		12
#define  CAUSEF_IP4		(_ULCAST_(1)   << 12)
#define  CAUSEB_IP5		13
#define  CAUSEF_IP5		(_ULCAST_(1)   << 13)
#define  CAUSEB_IP6		14
#define  CAUSEF_IP6		(_ULCAST_(1)   << 14)
#define  CAUSEB_IP7		15
#define  CAUSEF_IP7		(_ULCAST_(1)   << 15)
#define  CAUSEB_IV		23
#define  CAUSEF_IV		(_ULCAST_(1)   << 23)
#define  CAUSEB_CE		28
#define  CAUSEF_CE		(_ULCAST_(3)   << 28)
#define  CAUSEB_BD		31
#define  CAUSEF_BD		(_ULCAST_(1)   << 31)

#define CONF_CM_UNCACHED		2
#endif /* _ASM_REGDEF_H */
