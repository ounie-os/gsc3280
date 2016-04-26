/* simple malloc function */
#include <stdio.h>
#define AAT_SIZE 1024

//static unsigned char pile[64*1024];
static int initial = 0;

static unsigned int *pile_base = (unsigned int *)0x84000000;
typedef struct alloc_addr
{
    void *addr;
    unsigned int size;
    unsigned char flag;
} alloc_addr;

alloc_addr alloc_addr_table[AAT_SIZE];

void init_AAT(void)
{
    int i = 0;
//    pile_base = pile + 24;
    for(i=0;i<AAT_SIZE;i++)
    {
	alloc_addr_table[i].addr = 0;
	alloc_addr_table[i].size = 0;
	alloc_addr_table[i].flag = 0;
    }
}

void *get_free_mem(int size)
{
    int i = 0;
    int j = 0;
    void *prev = pile_base;
    for(i=0;i<AAT_SIZE;i++)
    {
	if (alloc_addr_table[i].flag)
	{
	    if (alloc_addr_table[i].addr - prev < size)
	    {
		prev = alloc_addr_table[i].addr + alloc_addr_table[i].size;
		continue;
	    }
	    else
	    {
		for (j = AAT_SIZE - 1; j>i; j--)
		{
		    if (!alloc_addr_table[j-1].flag)
			continue;
		    alloc_addr_table[j].addr = alloc_addr_table[j-1].addr;
		    alloc_addr_table[j].size = alloc_addr_table[j-1].size;
		    alloc_addr_table[j].flag = alloc_addr_table[j-1].flag;
		}
		alloc_addr_table[i].addr = prev;
		alloc_addr_table[i].size = size;
		alloc_addr_table[i].flag = 1;
		return alloc_addr_table[i].addr;
	    }
	}
	if (!alloc_addr_table[i].flag)
	{
	    alloc_addr_table[i].addr = prev;
	    alloc_addr_table[i].size = size;
	    alloc_addr_table[i].flag = 1;
	    return alloc_addr_table[i].addr;
	}
    }
    if (i == AAT_SIZE)
	panic("stack full");
    return 0;
}

void  *malloc(int size)
{
    if (!initial)
    {
	init_AAT();
	initial = 1;
    }
    void * base = NULL;
    base = get_free_mem(size);
    return base;
}

void free(void *base)
{
    int i = 0;
    int j = 0;
    for (i = 0;i < AAT_SIZE; i++)
    {
	if (alloc_addr_table[i].addr == base)
	    for(j=i;j<AAT_SIZE;j++)
	    {
		if (!alloc_addr_table[j].flag)
		    break;
		alloc_addr_table[j].addr = alloc_addr_table[j+1].addr;
		alloc_addr_table[j].size = alloc_addr_table[j+1].size;
		alloc_addr_table[j].flag = alloc_addr_table[j+1].flag;
	    }
    }
}
