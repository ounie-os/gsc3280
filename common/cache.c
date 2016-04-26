#include <stdio.h>
#include <asm/cacheops.h>

#define CONFIG_SYS_CACHELINE_SIZE 32 

struct dcache_buf_entry {
	unsigned int round;
	unsigned int idx;
	unsigned int taglo;
	unsigned int taghi;
};

struct dcache_buf_entry *dcache_buf_array = NULL;
int dcache_buf_round;
int dcache_buf_count;

#define cache_op(op,addr)                                               \
	__asm__ __volatile__(                                           \
	"       .set    push                                    \n"	\
	"       .set    noreorder                               \n"     \
	"       .set    mips3\n\t                               \n"     \
	"       cache   %0, %1                                  \n"     \
	"       .set    pop                                     \n"     \
	:                                                               \
	: "i" (op), "R" (*(unsigned char *)(addr)))


void flush_cache(unsigned long start_addr, unsigned long size)
{
        unsigned long lsize = CONFIG_SYS_CACHELINE_SIZE;
        unsigned long addr = start_addr & ~(lsize - 1);
        unsigned long aend = (start_addr + size - 1) & ~(lsize - 1);

        while (1) {
                cache_op(Hit_Writeback_Inv_D, addr);
                cache_op(Hit_Invalidate_I, addr);
                if (addr == aend)
                        break;
                addr += lsize;
        }
}

void dump_dcache_buf_init(void)
{
	struct dcache_buf_entry *buf = (struct dcache_buf_entry*)0xa2000000;
	dcache_buf_array = buf;
	dcache_buf_count = 0;
	dcache_buf_round = 0;
}

void dump_dcache_buf(void)
{
	unsigned long start = 0x80000000;
	unsigned long end = start + (4 << 10);
	unsigned long ws_inc = 1UL << 0;
	unsigned long ws_end = 2 << 0;
	unsigned long ws, addr = 0;
	unsigned int Taglo = 0, Taghi = 0;
	{
		for (ws = 0; ws < ws_end; ws += ws_inc)
		  for (addr = start; addr < end; addr += 32) {
			  __asm__ __volatile__ (
			   "	.set push					\n"
			   "	.set noreorder				\n"
			   "	.set mips32					\n"
			   "	cache %3, 0x000(%2);		\n"
			   "	nop\n"
			   "	mfc0 %0, $28, 0\n"
			   "	nop\n"
			   "	mfc0 %1, $29, 0\n"
			   "	nop\n"
			   "	.set mips0\n"
			   "	.set pop					\n"
			   :"=r" (Taglo), "=r" (Taghi)
			   :"r" (addr | ws), "i" (0x05));

				dcache_buf_array[dcache_buf_count].round = dcache_buf_round;
				dcache_buf_array[dcache_buf_count].idx = addr | ws;
				dcache_buf_array[dcache_buf_count].taglo = Taglo;
				dcache_buf_array[dcache_buf_count].taghi = Taghi;
				dcache_buf_count++;
		  }
	dcache_buf_round++;
	}
}

void dump_dcache_buf_print(void)
{
	int i;
	if (!dcache_buf_array) {
		printf("malloc dcache_buf_array failed\n");
	}

	for (i = 0; i < dcache_buf_count; i++) {
		printf("%d: %x %x %x %x\n", i, 
				dcache_buf_array[i].round,
				dcache_buf_array[i].idx,
				dcache_buf_array[i].taglo,
				dcache_buf_array[i].taghi);
	}

}

void dump_dcache(void)
{
	unsigned int start = 0x80000000;
	unsigned int end = start + (4 << 10);
	unsigned int ws_inc = 1UL << 0;
	unsigned int ws_end = 2 << 0;
	unsigned int ws, addr = 0;
	unsigned int Taglo = 0, Taghi = 0;
	{
		for (ws = 0; ws < ws_end; ws += ws_inc)
		  for (addr = start; addr < end; addr += 32) {
			  __asm__ __volatile__ (
			   "	.set push					\n"
			   "	.set noreorder				\n"
			   "	.set mips32					\n"
			   "	cache %3, 0x000(%2);		\n"
			   "	nop\n"
			   "	mfc0 %0, $28, 0\n"
			   "	nop\n"
			   "	mfc0 %1, $29, 0\n"
			   "	nop\n"
			   "	.set mips0\n"
			   "	.set pop					\n"
			   :"=r" (Taglo), "=r" (Taghi)
			   :"r" (addr | ws), "i" (0x05));

			  printf("%x: Taglo(%x) Taghi(%x)\n", addr | ws, Taglo, Taghi);
		  }
	}
}
