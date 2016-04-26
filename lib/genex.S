#include <asm/asm.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>
#include <asm/stackframe.h>

NESTED(except_vec3_generic, 0, sp)
        .set    push
        .set    noat
        mfc0    k1, CP0_CAUSE
        andi    k1, k1, 0x7c

        PTR_L   k0, exception_handlers(k1)
        jr      k0
        .set    pop
END(except_vec3_generic)

NESTED(handle_int, PT_SIZE, sp)
        SAVE_ALL
        CLI

        LONG_L  s0, TI_REGS($28)
        LONG_S  sp, TI_REGS($28)
	PTR_LA t9, irq_dispatch
        jalr	t9
	nop
	LONG_S  s0, TI_REGS($28)
        RESTORE_TEMP
        RESTORE_AT
        RESTORE_STATIC
        RESTORE_SOME
        RESTORE_SP_AND_RET
END(handle_int)

NESTED(handle_reserved, PT_SIZE, sp)
	.set mips3
	eret
	.set mips0
END(handle_reserved)
