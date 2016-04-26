#define __ASSEMBLY__
#include <asm/asm.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>
#include <asm/cacheops.h>

//#define CONFIG_UART_EARLY_PRINT

#ifdef CONFIG_UART_EARLY_PRINT
#define GC_COM0_BASE 0xbc108000
#define COM_DLL	(5560000 /(115200 * 8 ))
#define GC_COM0_DATA  (GC_COM0_BASE + 0x0)
#define GC_COM0_GC   (GC_COM0_BASE + 0x2)
#define GC_COM0_LSR   (GC_COM0_BASE + 0x5)
#define PRINTSTR(x) \
        .rdata;98: .asciz x; .text; la a0, 98b;bal puts_raw; nop

	.macro uart_init_early
	.set	push
	li	a0, GC_COM0_BASE
	move	t1, zero
	ori	t1, 0x80	# set DLAB = 1
	addu	a2, a0, 3
	sb		t1, (a2)	# LCR (Line Control Register)

	li		t1, COM_DLL
	addu		a2, a0, 0
	sb		t1, (a2)	# DLL (Divide Latch, LSB)

	srl     	t1,8
	addu		a2, a0, 1
	sb		t1, (a2)	# DLM (Divisor Latch, MSB)

	li		t1, 0x03
	addu		a2, a0, 3
	sb		t1, (a2)	# LCR (Line Control Register)
	
	li		t1, 0x47	# RCVR Trigger & FIFO Enable
	addu		a2, a0, 2		# reset Tx/Rx Fifo
	sb		t1, (a2)	# GC (Fifo Control Register)
	.set	pop
	.endm
#endif

	.macro mips_cache_reset_nogot
	.set push
	.set noreorder
	.set mips3

	lui    a0, 0xa100
	ori    a0, a0, 0  # a0 = 0xa0000000
	li     a1, 0x10000 # 64 k
	
	addu   v0, $0, a0
	addu   v1, a0, a1

1:      addiu   v0, 64
	sw	zero,-64(v0)
	sw	zero,-60(v0)
	sw	zero,-56(v0)
	sw	zero,-52(v0)
	sw	zero,-48(v0)
	sw	zero,-44(v0)
	sw	zero,-40(v0)
	sw	zero,-36(v0)
	sw	zero,-32(v0)
	sw	zero,-28(v0)
	sw	zero,-24(v0)
	sw	zero,-20(v0)
	sw	zero,-16(v0)
	sw	zero,-12(v0)
	sw	zero,-8(v0)
        bne     v0, v1, 1b
	sw	zero,-4(v0)

/* icache_invalidate 16K ,4way ,linesize = 32 */

	lui    a0, 0x8100
	ori    a0, a0, 0  # a0 = 0x80000000
	li     a1, 0x1000 # 4 k
	
	addu   v0, $0, a0
	addu   v1, a0, a1

1:
	cache  Index_Invalidate_I, 0x0(v0) #1 way
	cache  Index_Invalidate_I, 0x1(v0) #2 way
	cache  Index_Invalidate_I, 0x2(v0) #3 way
	cache  Index_Invalidate_I, 0x3(v0) #4 way
	bge    v1, v0, 1b   	
	addiu  v0, v0, 0x20 # if v0 >= v1 go 1b

/*clear dcache tag */

	mtc0	zero, CP0_TAGLO
	mtc0	zero, CP0_TAGHI
	lui	a0, 0x8100
	ori	a0, a0, 0  # a0 = 0x80000000
	li	a1, 0x1000 # 4 k
	
	addu	v0, $0, a0
	addu	v1, a0, a1
1:
	cache	Index_Store_Tag_D, 0x0(v0) #1 way
	cache	Index_Store_Tag_D, 0x1(v0) #2 way
	cache   Index_Store_Tag_D, 0x2(v0) #3 way
	cache   Index_Store_Tag_D, 0x3(v0) #4 way
	bge	v1, v0, 1b   	
	addiu	v0, v0, 0x20 # if v0 >= v1 go 1b

/*fill dcache*/

	mtc0	zero, CP0_TAGLO
	mtc0	zero, CP0_TAGHI
	lui    a0, 0x8100
	ori    a0, a0, 0x1000  # a0 = 0x80000000
	li     a1, 0x1000 # 4 k
	
	addu   v0, $0, a0
	addu   v1, a0, a1
1:
	cache  Index_Writeback_Inv_D, 0x0(v0) #1 way
	cache  Index_Writeback_Inv_D, 0x1(v0) #2 way
        cache  Index_Writeback_Inv_D, 0x2(v0) #3 way
        cache  Index_Writeback_Inv_D, 0x3(v0) #4 way
	bge    v1, v0, 1b   	
	addiu  v0, v0, 0x20 # if v0 >= v1 go 1b

/*clear dcache tag again*/

	mtc0	zero, CP0_TAGLO
	mtc0	zero, CP0_TAGHI
	lui	a0, 0x8100
	ori	a0, a0, 0  # a0 = 0x80000000
	li	a1, 0x1000 # 4 k
	
	addu	v0, $0, a0
	addu	v1, a0, a1
1:
	cache	Index_Store_Tag_D, 0x0(v0) #1 way
	cache	Index_Store_Tag_D, 0x1(v0) #2 way
        cache   Index_Store_Tag_D, 0x2(v0) #3 way
        cache   Index_Store_Tag_D, 0x3(v0) #4 way
	bge	v1, v0, 1b   	
	addiu	v0, v0, 0x20 # if v0 >= v1 go 1b
	.set pop
	.endm

	.macro flush_cache_nogot
	.set push
	.set noreorder
	.set mips3
	li	v1,-32
	addiu	v0,a0,-1
	addu	v0,v0,a1
	and	v0,v0,v1
	and	a0,a0,v1
1:
	cache	Hit_Writeback_Inv_D,0(a0)
	cache	Hit_Invalidate_I,0(a0)
	bne	a0,v0,1b	
	addiu 	a0,a0,32	
	.set pop
	.endm


	/*
	 * For the moment disable interrupts, mark the kernel mode and
	 * set ST0_KX so that the CPU does not spit fire when using
	 * 64-bit addresses.
	 */
	.macro	setup_c0_status set clr
	.set	push
	mfc0	t0, CP0_STATUS
	or	t0, ST0_CU0 | \set | 0x1f | \clr
	xor	t0, 0x1f | \clr
	mtc0	t0, CP0_STATUS
	.set	noreorder
	sll	zero, 3				# ehb
	.set	pop
	.endm




#define RVECENT(f,n) \
   b f; nop
#define XVECENT(f,bev) \
   b f     ;           \
   li k0,bev

	.set noreorder

	.globl _start
	.text
_start:
	RVECENT(reset,0)	/* entry point */
	RVECENT(reset,1)	/* software reboot */
	RVECENT(romReserved,2)
	RVECENT(romReserved,3)
	RVECENT(romReserved,4)
	RVECENT(romReserved,5)
	RVECENT(romReserved,6)
	RVECENT(romReserved,7)
	RVECENT(romReserved,8)
	RVECENT(romReserved,9)
	RVECENT(romReserved,10)
	RVECENT(romReserved,11)
	RVECENT(romReserved,12)
	RVECENT(romReserved,13)
	RVECENT(romReserved,14)
	RVECENT(romReserved,15)
	RVECENT(romReserved,16)
	RVECENT(romReserved,17)
	RVECENT(romReserved,18)
	RVECENT(romReserved,19)
	RVECENT(romReserved,20)
	RVECENT(romReserved,21)
	RVECENT(romReserved,22)
	RVECENT(romReserved,23)
	RVECENT(romReserved,24)
	RVECENT(romReserved,25)
	RVECENT(romReserved,26)
	RVECENT(romReserved,27)
	RVECENT(romReserved,28)
	RVECENT(romReserved,29)
	RVECENT(romReserved,30)
	RVECENT(romReserved,31)
	RVECENT(romReserved,32)
	RVECENT(romReserved,33)
	RVECENT(romReserved,34)
	RVECENT(romReserved,35)
	RVECENT(romReserved,36)
	RVECENT(romReserved,37)
	RVECENT(romReserved,38)
	RVECENT(romReserved,39)
	RVECENT(romReserved,40)
	RVECENT(romReserved,41)
	RVECENT(romReserved,42)
	RVECENT(romReserved,43)
	RVECENT(romReserved,44)
	RVECENT(romReserved,45)
	RVECENT(romReserved,46)
	RVECENT(romReserved,47)
	RVECENT(romReserved,48)
	RVECENT(romReserved,49)
	RVECENT(romReserved,50)
	RVECENT(romReserved,51)
	RVECENT(romReserved,52)
	RVECENT(romReserved,53)
	RVECENT(romReserved,54)
	RVECENT(romReserved,55)
	RVECENT(romReserved,56)
	RVECENT(romReserved,57)
	RVECENT(romReserved,58)
	RVECENT(romReserved,59)
	RVECENT(romReserved,60)
	RVECENT(romReserved,61)
	RVECENT(romReserved,62)
	RVECENT(romReserved,63)
	XVECENT(romExcHandle,0x200)	/* bfc00200: R4000 tlbmiss vector */
	RVECENT(romReserved,65)
	RVECENT(romReserved,66)
	RVECENT(romReserved,67)
	RVECENT(romReserved,68)
	RVECENT(romReserved,69)
	RVECENT(romReserved,70)
	RVECENT(romReserved,71)
	RVECENT(romReserved,72)
	RVECENT(romReserved,73)
	RVECENT(romReserved,74)
	RVECENT(romReserved,75)
	RVECENT(romReserved,76)
	RVECENT(romReserved,77)
	RVECENT(romReserved,78)
	RVECENT(romReserved,79)
	XVECENT(romExcHandle,0x280)	/* bfc00280: R4000 xtlbmiss vector */
	RVECENT(romReserved,81)
	RVECENT(romReserved,82)
	RVECENT(romReserved,83)
	RVECENT(romReserved,84)
	RVECENT(romReserved,85)
	RVECENT(romReserved,86)
	RVECENT(romReserved,87)
	RVECENT(romReserved,88)
	RVECENT(romReserved,89)
	RVECENT(romReserved,90)
	RVECENT(romReserved,91)
	RVECENT(romReserved,92)
	RVECENT(romReserved,93)
	RVECENT(romReserved,94)
	RVECENT(romReserved,95)
	XVECENT(romExcHandle,0x300)	/* bfc00300: R4000 cache vector */
	RVECENT(romReserved,97)
	RVECENT(romReserved,98)
	RVECENT(romReserved,99)
	RVECENT(romReserved,100)
	RVECENT(romReserved,101)
	RVECENT(romReserved,102)
	RVECENT(romReserved,103)
	RVECENT(romReserved,104)
	RVECENT(romReserved,105)
	RVECENT(romReserved,106)
	RVECENT(romReserved,107)
	RVECENT(romReserved,108)
	RVECENT(romReserved,109)
	RVECENT(romReserved,110)
	RVECENT(romReserved,111)
	XVECENT(romExcHandle,0x380)	/* bfc00380: R4000 general vector */
	RVECENT(romReserved,113)
	RVECENT(romReserved,114)
	RVECENT(romReserved,115)
	RVECENT(romReserved,116)
	RVECENT(romReserved,116)
	RVECENT(romReserved,118)
	RVECENT(romReserved,119)
	RVECENT(romReserved,120)
	RVECENT(romReserved,121)
	RVECENT(romReserved,122)
	RVECENT(romReserved,123)
	RVECENT(romReserved,124)
	RVECENT(romReserved,125)
	RVECENT(romReserved,126)
	RVECENT(romReserved,127)

	/* We hope there are no more reserved vectors!
	 * 128 * 8 == 1024 == 0x400
	 * so this is address R_VEC+0x400 == 0xbfc00400
	 */
	.align 4
reset:

	/* Clear watch registers.
	 */
	mtc0	zero, CP0_WATCHLO
	mtc0	zero, CP0_WATCHHI

	/* WP(Watch Pending), SW0/1 should be cleared. */
	mtc0	zero, CP0_CAUSE

	/* Init Timer */
	mtc0	zero, CP0_COUNT
	mtc0	zero, CP0_COMPARE

#init sysctrl
	li	a0, 0xbc04a00c
	lw	t1,(a0)
	ori	t1,0x10		#sysctrl clk enable
	sw	t1, (a0)	# SYSCTRL:MOD_CTL1

	li	a0,0xbc04a0b0
	lw	t1,(a0)
/*uart0:13 IO*/
	li 	a1,0x2000
	or	t1,a1
	sw	t1,(a0)

	li	a0, 0xbc04a008
	lw	t1,(a0)
/*uart0:14 clk enable */
	li	a1,0x10000
	or	t1,a1
	sw	t1, (a0)	# SYSCTRL:MOD_CTL0 

#ifdef CONFIG_UART_EARLY_PRINT
	uart_init_early
#endif

	//PRINTSTR("this is early print!!..........ok!!\n");
	/* CONFIG0 register */
	mfc0	t0, CP0_CONFIG
	srl		t0, 3
	sll		t0, 3
	ori		t0, CONF_CM_UNCACHED
	mtc0	t0, CP0_CONFIG
	nop

	/* Initialize $gp.
	 */
	bal	1f
	nop
	.word	_gp
1:
	lw	gp, 0(ra)
#enable cache

	mips_cache_reset_nogot 
     
	li	t0, CONF_CM_CACHABLE_NONCOHERENT
	mfc0	t1, CP0_CONFIG
	or		t1, t0
	mtc0	t1, CP0_CONFIG
	la	t0, 0x80000000 + 0x10000 #use lower 1MB as stack before relocation
	move	sp, t0

	la		t0,bss
	jr		t0
	nop

	.word	boot_end_data
	.word	boot_end
bss:
	/* Clear BSS.
	 */
	lw	t1, -8(t0)	/* t1 <-- boot_end_data	*/
	lw	t2, -4(t0)	/* t2 <-- boot_end		*/

	sub	t1, 4
1:
	addi	t1, 4
	bltl	t1, t2, 1b
	sw	zero, 0(t1)	/* delay slot			*/

	la	t9, start_test
	jr	t9
	nop

	/* Exception handlers.
	 */
romReserved:
#if 1
	b	romReserved
	nop
#else
	la t9, dump_dcache_buf
	jr t9
	nop
#endif

romExcHandle:
	b	romExcHandle
	nop

#ifdef CONFIG_UART_EARLY_PRINT
/* destroy: a0,a1 t0,t1(com_outch), t9 */
LEAF(puts_raw)
	.set noreorder
        move    v1, ra
        move    a1, a0
        lbu     a0, 0(a1)
1:
        beqz    a0, 2f
        nop
        bal     com_outch
        addiu   a1, 1
        b       1b
        lbu     a0, 0(a1)

2:
        jr       v1
        nop
	.set reorder
END(puts_raw)

/* destroy: t0,t1,ra */
LEAF(com_outch)

1:	lbu	v0, (GC_COM0_LSR)		
    	and	v0, 0x20			
	beqz	v0, 1b				
	nop

1:	sb	a0, (GC_COM0_DATA)	
	jr	ra
	nop
END(com_outch)	
#endif
