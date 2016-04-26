/* $Id: sprintf.c,v 1.1.1.1 2006/05/25 02:11:24 cpu Exp $ */
#include <stdio.h>

/*
 *  int vprintf(fmt,ap)
 */
static char buf[1024];

int sprintf (const char *fmt, ...)
{
    int  len;
    char *ap;

    ap = (char *)(&fmt) + 4;
    len = vsprintf (buf, fmt, ap);
    return (len);
}


