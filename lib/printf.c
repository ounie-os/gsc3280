/* $Id: printf.c,v 1.1.1.1 2006/05/25 02:11:24 cpu Exp $ */
#include <stdio.h>
#include <console.h>
/*
 *  int vprintf(fmt,ap)
 */
//static char buf[1024];

int
vprintf (const char *fmt, const char * ap)
{
    int n;
    int i;

	static char buf[1024];
    memset (buf, 0, 1024);

    n = vsprintf (buf, fmt, ap);

    for (i = 0; i < n; i++) {
	if (buf[i] == '\n')
	    console_putc ('\r');
	console_putc (buf[i]);
    }

    return n;
}

int printf (const char *fmt, ...)
{
    int  len;
    char *ap;

    ap = (char *)(&fmt) + 4;
    len = vprintf (fmt, ap);
    return (len);
}


