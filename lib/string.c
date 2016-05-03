/* Simple string functions */
#include <stdio.h>

#include "string.h" 

int strlen(char * str)
{
	const char *sc;

	for (sc = str; *sc != '\0'; ++sc)
		/* nothing */;
	return sc - str;
}




void strcpy(char *to, char *from)
{

//	char *tmp = to;
	while((*to++ = *from++) != '\0');

}

/*
int strcmp(char *to, char *from)
{
	int i,j;
	int count = 0;
	i = strlen(to);
	j = strlen(from);
	for (count=0;count<j;count++)
	{
		i--;
		if (to[count] == from[count])
			continue;
		else
		{
			if (to[count] > from[count])
				return 1;
			else
				return -1;
		}
		if (i == 0)
			return -1;
	}
	if (i)
		return 1;
	return 0;
}
*/

int strcmp(char * to,char * from)
{
	register signed char __res;

	while (1) {
		if ((__res = *to - *from++) != 0 || !*to++)
			break;
	}

	return __res;
}


int strstr(char *s1, char *s2)
{
	int len1, len2;
	int i = 0;

	len1 = strlen(s1);
	len2 = strlen(s2);
	if (len2 > len1)
		return -1;
	for (i = 0; i<len2; i++)
		if (s1[i] != s2[i])
			return -1;
	return 0;
}

/** str_fmt(p,size,fmt) format p in a field size in width using fmt */
void str_fmt (char *p, int size, int fmt)
{
	int             n, m, len;

	len = strlen (p);
	switch (fmt) {
		case FMT_RJUST:
			for (n = size - len; n > 0; n--)
				strichr (p, ' ');
			break;
		case FMT_LJUST:
			for (m = size - len; m > 0; m--)
				strcat (p, " ");
			break;
		case FMT_RJUST0:
			for (n = size - len; n > 0; n--)
				strichr (p, '0');
			break;
		case FMT_CENTER:
			m = (size - len) / 2;
			n = size - (len + m);
			for (; m > 0; m--)
				strcat (p, " ");
			for (; n > 0; n--)
				strichr (p, ' ');
			break;
	}
}

/** char *strcat(dst,src)  concatinate src string to dst string */
char *strcat (char *dst, char *src)
{
	char           *d;

	if (!dst || !src)
		return (dst);
	d = dst;
	for (; *d; d++);
	for (; *src; src++)
		*d++ = *src;
	*d = 0;
	return (dst);
}

/** char *strchr(p,c) return a ptr to c in p, return NUL if not found */
char *strchr (char *p, char c)
{
	if (!p)
		return (0);

	for (; *p; p++)
		if (*p == c)
			return (p);
	return (0);
}


/** char *strichr(p,c) inserts c as the first char of the string p */
char *strichr (char *p, int c)
{
	char           *t;

	if (!p)
		return (p);
	for (t = p; *t; t++);
	for (; t >= p; t--)
		*(t + 1) = *t;
	*p = c;
	return (p);
}

/** char *strncpy(dst,src,n) copy n chars from src to dst */
char *strncpy (char *dst,char *src,int n)
{
	char *d;

	if (!dst || !src)
		return (dst);
	d = dst;
	for (; *src && n; d++, src++, n--)
		*d = *src;
	while (n--)
		*d++ = '\0';
	return (dst);
}

#if 0
/** toupper(c) translate c to uppercase */
int toupper (int c)
{
	if (islower (c))
		return (c - ('a' - 'A'));
	return (c);
}
#endif
/** strtoupper(p) convert p to uppercase */
void strtoupper (char *p)
{
	if (!p)
		return;
	for (; *p; p++)
		*p = toupper (*p);
}



char *strblank(char *buf, int num)
{
	int i = 0;
	int start = 0;
	while (num && i < strlen(buf))
	{
		if (start == 0)
		{
			if (buf[i] == ' ')
			{
				i++;
				continue;
			}
			else
			{
				if (buf[i] == 0)
					return NULL;
				start = 1;
			}
		}
		else
		{
			if (buf[i] != ' ')
			{
				i++;
				continue;
			}
			else
			{
				start = 0;
				num--;
			}
		}
	}
	if (num)
		return NULL;
	else
		return buf + i;
}

char *strunblank(char *buf, int num)
{
	int i = 0;
	int start = 0; //found = 0;
	while (num && i < strlen(buf))
	{
		if (start == 0)
		{
			if (buf[i] == ' ')
			{
				i++;
				continue;
			}
			else
			{
				if (buf[i] == 0)
					return NULL;
				num--;
				start = 1;
			}
		}
		else
		{
			if (buf[i] != ' ')
			{
				i++;
				continue;
			}
			else 
				start = 0;
		}
	}
	if (num)
		return NULL;
	else
		return buf + i;
}
int strncmp(const char * cs,const char * ct,int count)
{
        register signed char __res = 0;

        while (count) {
                if ((__res = *cs - *ct++) != 0 || !*cs++)
                        break;
                count--;
        }

        return __res;
}

unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base)
{
	unsigned long result = 0,value;

	if (*cp == '0') {
		cp++;
		if ((*cp == 'x') && isxdigit(cp[1])) {
			base = 16;
			cp++;
		}
		if (!base) {
			base = 8;
		}
	}
	if (!base) {
		base = 10;
	}
	while (isxdigit(*cp) && (value = isdigit(*cp) ? *cp-'0' : (islower(*cp)
	    ? toupper(*cp) : *cp)-'A'+10) < base) {
		result = result*base + value;
		cp++;
	}
	if (endp)
		*endp = (char *)cp;
	return result;
}

