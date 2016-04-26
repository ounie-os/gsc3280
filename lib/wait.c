void wait(int t)
{
	while (t--);
}

void udelay(int t)
{

	__udelay(t);
/*
    int i;
    i = t*CPU_FREQ_MHZ/2;
    __asm__ __volatile__(
	    "li   $10, 0\n\t"
	    "mtc0 $10, $9\n\t"
	    "1:\n\t"
	    "mfc0 $10, $9\n\t"
	    "sub  $11, %0, $10\n"
	    "bgtz $11, 1b\n\t"
	    "nop\n"
	    :
	    :"r"(i)
	    );
*/
}
void mdelay(int t)
{
	udelay(t*1000);
}
