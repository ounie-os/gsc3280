/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1998 by Ralf Baechle
 */
#include <asm.h>
#include <mipsregs.h>
#include <regdef.h>
#include <address.h>

#define EXE(insn,reg,addr)			\
9:	insn	reg, addr;				

#define F_FILL64(dst, offset, val)		\
	EXE(sw, val, (offset + 0x00)(dst));	\
	EXE(sw, val, (offset + 0x04)(dst));	\
	EXE(sw, val, (offset + 0x08)(dst));	\
	EXE(sw, val, (offset + 0x0c)(dst));	\
	EXE(sw, val, (offset + 0x10)(dst));	\
	EXE(sw, val, (offset + 0x14)(dst));	\
	EXE(sw, val, (offset + 0x18)(dst));	\
	EXE(sw, val, (offset + 0x1c)(dst));	\
	EXE(sw, val, (offset + 0x20)(dst));	\
	EXE(sw, val, (offset + 0x24)(dst));	\
	EXE(sw, val, (offset + 0x28)(dst));	\
	EXE(sw, val, (offset + 0x2c)(dst));	\
	EXE(sw, val, (offset + 0x30)(dst));	\
	EXE(sw, val, (offset + 0x34)(dst));	\
	EXE(sw, val, (offset + 0x38)(dst));	\
	EXE(sw, val, (offset + 0x3c)(dst))

/*
 * memset(void *s, int c, size_t n)
 *
 * a0: start of area to clear
 * a1: char to fill with
 * a2: size of area to clear
 */
	.set	noreorder
	.align	5
LEAF(memset)
	beqz	a1, 1f
	 move	v0, a0				/* result */

	andi	a1, 0xff			/* spread fillword */
	sll	t1, a1, 8
	or	a1, t1
	sll	t1, a1, 16
	or	a1, t1
1:

EXPORT(__bzero)
	.type   __bzero, @function
	sltiu	t0, a2, 4			/* very small region? */
	bnez	t0, small_memset
	 andi	t0, a0, 3			/* aligned? */

	beqz	t0, 1f
	 subu	t0, 4				/* alignment in bytes */

#	EXE(swr, a1, (a0))		/* make word aligned */
	move	t2, t0
11: and		t3, a1, 0xff
	sb		t3, (a0)
	srl		t3, 8
	subu	t2, 1
	bnez	t2, 11b
	nop
	subu	a0, t0				/* word align ptr */
	addu	a2, t0				/* correct size */

1:	ori	t1, a2, 0x3f			/* # of full blocks */
	xori	t1, 0x3f
	beqz	t1, memset_partial		/* no block to fill */
	 andi	t0, a2, 0x3c

	addu	t1, a0				/* end address */
	.set	reorder
1:	addiu	a0, 64
	F_FILL64(a0, -64, a1)
	bne	t1, a0, 1b
	.set	noreorder

memset_partial:
	la	t1, 2f				/* where to start */
	subu	t1, t0
	jr	t1
	 addu	a0, t0				/* dest ptr */

	F_FILL64(a0, -64, a1)	/* ... but first do wrds ... */
2:	andi	a2, 3				/* 0 <= n <= 3 to go */

	beqz	a2, 1f
#	addu	a0, a2				/* What's left */
#	EXE(swl, a1, -1(a0))
	move	t0, a1
11:
	sb		t0, (a0)
	add		a0, 1
	sub		a2, 1
	bnez	a2, 11b
	nop
1:	jr	ra
	 move	a2, zero

small_memset:
	beqz	a2, 2f
    addu	t1, a0, a2

1:	addiu	a0, 1				/* fill bytewise */
	bne	t1, a0, 1b
	sb	a1, -1(a0)

2:	jr	ra				/* done */
	 move	a2, zero
	END(memset)



