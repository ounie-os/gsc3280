#include <stdio.h>
#include <console.h>

void iptx(unsigned int *value, char *ip)
{
	int len = strlen(ip);
	int i = 0;
	int j = 0;
	unsigned int prev;
	unsigned char *p = (unsigned char *)value;
	char tmp[5];

	*value = 0;
	for (i=0;i<=len;i++,j++)
	{
		if (ip[i] != '.' && i < len)
			tmp[j] = ip[i];
		else
		{
			tmp[j] = 0;
			j = -1;
			stx(&prev, tmp);
			*value = (*value << 8) | prev;
		}
	}
	prev = p[0];
	p[0] = p[3];
	p[3] = prev;
	prev = p[1];
	p[1] = p[2];
	p[2] = prev;
}

void bts(unsigned char *c, unsigned char b)
{
	unsigned char tmp1,tmp2;
	tmp1 = b & 0x0f;
	tmp2 = (b >> 4) & 0x0f;
	if(tmp1 < 10)
		c[1] = '0' + tmp1;
	else
		c[1] = 'a' + (tmp1 - 10);

	if(tmp2 < 10)
		c[0] = '0' + tmp2;
	else
		c[0] = 'a' + (tmp2 - 10);
}

int stx(unsigned int *result, char *buf)
{
	int right = 10;
	int len = 0;
	char *pos=NULL;
	int i = 0;

	if(buf[0]=='0' && (buf[1]=='x'|| buf[1]=='X'))
		right = 16;
	*result = 0;

	if (right == 10)
	{
		len = strlen(buf);
		if (len > 10)
			return 1;
		pos = buf;
		for (i=0;i<len;i++)
		{
			if (pos[i] < '0' || pos[i] > '9')
				return 1;
			*result = (*result*10) + (pos[i]-'0');
		}
	}else
	{
		len = strlen(buf + 2);
		if (len > 8)
			return 1;
		pos = buf + 2;
		for (i=0;i<len;i++)
		{
			if (pos[i] >= '0' && pos[i] <= '9')
				*result = (*result << 4) | (pos[i] - '0');
			else if (pos[i] >= 'a' && pos[i] <= 'f')
				*result = (*result << 4) | (pos[i] - 'a' + 10);
			else if (pos[i] >= 'A' && pos[i] <= 'F')
				*result = (*result << 4) | (pos[i] - 'A' + 10);
			else
				return 1;
		}
	}
	return 0;
}

void dump_data(void *buf, int size)
{
	char tow_char[3];
	int i = 0, j = 0;

	if (buf == NULL)
	    return;

	tow_char[2] = 0;
	for(i=0,j=0;i<size;i++)
	{
		bts((unsigned char *)tow_char, ((unsigned char *)buf)[i]);
		if (!(i % 32))
			console_puts("\r\n");
		else if (!(i % 4))
			console_puts(" ");
		console_puts(tow_char);
	}
	console_puts("\r\n");
}
