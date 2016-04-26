/* simple memory copy function */
void memcpy(void *to, void *from, int size)
{
	int i;
	unsigned int src_off, dst_off;

	src_off = (unsigned int)from & 3;
	dst_off = (unsigned int)to & 3;

	if (!(src_off | dst_off))
	{
		if (size > 256)
		{
			for(i =0; i<size/256; i++){
				*(unsigned int*)(to) = *(unsigned int*)(from);
				*(unsigned int*)(to+4) = *(unsigned int*)(from+4);
				*(unsigned int*)(to+8) = *(unsigned int*)(from+8);
				*(unsigned int*)(to+12) = *(unsigned int*)(from+12);
				*(unsigned int*)(to+16) = *(unsigned int*)(from+16);
				*(unsigned int*)(to+20) = *(unsigned int*)(from+20);
				*(unsigned int*)(to+24) = *(unsigned int*)(from+24);
				*(unsigned int*)(to+28) = *(unsigned int*)(from+28);
				*(unsigned int*)(to+32) = *(unsigned int*)(from+32);
				*(unsigned int*)(to+36) = *(unsigned int*)(from+36);
				*(unsigned int*)(to+40) = *(unsigned int*)(from+40);
				*(unsigned int*)(to+44) = *(unsigned int*)(from+44);
				*(unsigned int*)(to+48) = *(unsigned int*)(from+48);
				*(unsigned int*)(to+52) = *(unsigned int*)(from+52);
				*(unsigned int*)(to+56) = *(unsigned int*)(from+56);
				*(unsigned int*)(to+60) = *(unsigned int*)(from+60);
				to += 64;
				from += 64;
				*(unsigned int*)(to) = *(unsigned int*)(from);
				*(unsigned int*)(to+4) = *(unsigned int*)(from+4);
				*(unsigned int*)(to+8) = *(unsigned int*)(from+8);
				*(unsigned int*)(to+12) = *(unsigned int*)(from+12);
				*(unsigned int*)(to+16) = *(unsigned int*)(from+16);
				*(unsigned int*)(to+20) = *(unsigned int*)(from+20);
				*(unsigned int*)(to+24) = *(unsigned int*)(from+24);
				*(unsigned int*)(to+28) = *(unsigned int*)(from+28);
				*(unsigned int*)(to+32) = *(unsigned int*)(from+32);
				*(unsigned int*)(to+36) = *(unsigned int*)(from+36);
				*(unsigned int*)(to+40) = *(unsigned int*)(from+40);
				*(unsigned int*)(to+44) = *(unsigned int*)(from+44);
				*(unsigned int*)(to+48) = *(unsigned int*)(from+48);
				*(unsigned int*)(to+52) = *(unsigned int*)(from+52);
				*(unsigned int*)(to+56) = *(unsigned int*)(from+56);
				*(unsigned int*)(to+60) = *(unsigned int*)(from+60);
				to += 64;
				from += 64;
				*(unsigned int*)(to) = *(unsigned int*)(from);
				*(unsigned int*)(to+4) = *(unsigned int*)(from+4);
				*(unsigned int*)(to+8) = *(unsigned int*)(from+8);
				*(unsigned int*)(to+12) = *(unsigned int*)(from+12);
				*(unsigned int*)(to+16) = *(unsigned int*)(from+16);
				*(unsigned int*)(to+20) = *(unsigned int*)(from+20);
				*(unsigned int*)(to+24) = *(unsigned int*)(from+24);
				*(unsigned int*)(to+28) = *(unsigned int*)(from+28);
				*(unsigned int*)(to+32) = *(unsigned int*)(from+32);
				*(unsigned int*)(to+36) = *(unsigned int*)(from+36);
				*(unsigned int*)(to+40) = *(unsigned int*)(from+40);
				*(unsigned int*)(to+44) = *(unsigned int*)(from+44);
				*(unsigned int*)(to+48) = *(unsigned int*)(from+48);
				*(unsigned int*)(to+52) = *(unsigned int*)(from+52);
				*(unsigned int*)(to+56) = *(unsigned int*)(from+56);
				*(unsigned int*)(to+60) = *(unsigned int*)(from+60);
				to += 64;
				from += 64;
				*(unsigned int*)(to) = *(unsigned int*)(from);
				*(unsigned int*)(to+4) = *(unsigned int*)(from+4);
				*(unsigned int*)(to+8) = *(unsigned int*)(from+8);
				*(unsigned int*)(to+12) = *(unsigned int*)(from+12);
				*(unsigned int*)(to+16) = *(unsigned int*)(from+16);
				*(unsigned int*)(to+20) = *(unsigned int*)(from+20);
				*(unsigned int*)(to+24) = *(unsigned int*)(from+24);
				*(unsigned int*)(to+28) = *(unsigned int*)(from+28);
				*(unsigned int*)(to+32) = *(unsigned int*)(from+32);
				*(unsigned int*)(to+36) = *(unsigned int*)(from+36);
				*(unsigned int*)(to+40) = *(unsigned int*)(from+40);
				*(unsigned int*)(to+44) = *(unsigned int*)(from+44);
				*(unsigned int*)(to+48) = *(unsigned int*)(from+48);
				*(unsigned int*)(to+52) = *(unsigned int*)(from+52);
				*(unsigned int*)(to+56) = *(unsigned int*)(from+56);
				*(unsigned int*)(to+60) = *(unsigned int*)(from+60);
				to += 64;
				from += 64;
			}
			size %=256;
		}
		if(size >32){
			for(i =0; i< size/32; i++){
				*(unsigned int*)(to) = *(unsigned int*)(from);
				*(unsigned int*)(to+4) = *(unsigned int*)(from+4);
				*(unsigned int*)(to+8) = *(unsigned int*)(from+8);
				*(unsigned int*)(to+12) = *(unsigned int*)(from+12);
				*(unsigned int*)(to+16) = *(unsigned int*)(from+16);
				*(unsigned int*)(to+20) = *(unsigned int*)(from+20);
				*(unsigned int*)(to+24) = *(unsigned int*)(from+24);
				*(unsigned int*)(to+28) = *(unsigned int*)(from+28);
				to+=32;
				from+=32;
			}	
			size %= 32;
		}

		for (i=0;i<size/4;i++)
		{
				*(unsigned int*)(to) = *(unsigned int*)(from);
				to += 4;
				from += 4;
		}
		size %= 4;
	}

	for (i=0;i<size;i++)
	{
		*(unsigned char *)(to++) = *(unsigned char *)(from++);
	}
}

void memset(void *buf, unsigned char c, int len)
{
	int i;
	unsigned int off;
	off = ((unsigned int)buf) & 3;
#if 1
	if (off == 0)
	{
		for (i = 0; i<len/128; i++)
		{
				((unsigned int *)buf)[0] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+1] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+2] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+3] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+4] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+5] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+6] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+7] = c<<24|c<<16|c<<8|c;
				buf += 32;
				((unsigned int *)buf)[0] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+1] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+2] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+3] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+4] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+5] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+6] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+7] = c<<24|c<<16|c<<8|c;
				buf += 32;
				((unsigned int *)buf)[0] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+1] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+2] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+3] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+4] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+5] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+6] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+7] = c<<24|c<<16|c<<8|c;
				buf += 32;
				((unsigned int *)buf)[0] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+1] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+2] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+3] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+4] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+5] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+6] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+7] = c<<24|c<<16|c<<8|c;
				buf += 32;
		}
		len %= 128;
		for (i=0;i<len/32;i++)
		{
				((unsigned int *)buf)[0] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+1] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+2] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+3] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+4] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+5] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+6] = c<<24|c<<16|c<<8|c;
				((unsigned int *)buf)[0+7] = c<<24|c<<16|c<<8|c;
				buf += 32;
		}
		len %= 32;
		for (i = 0; i<len/4; i++)
				((unsigned int *)buf)[i] = c<<24|c<<16|c<<8|c;
		buf += (len & ~3);
		len %= 4;
	}
#endif
	for (i = 0; i<len; i++)
		((unsigned char *)buf)[i] = c;
}

char * bcopy(const char * src, char * dest, int count)
{
	char *tmp = dest;

	while (count--)
		*tmp++ = *src++;

	return dest;
}
