/* $Id: vsprintf.c,v 1.1.1.1 2006/05/25 02:11:24 cpu Exp $ */
#include <stdio.h>

#if 0
/** isdigit(c) returns true if c is decimal digit */
int isdigit (c)
     int             c;
{
    if (c >= '0' && c <= '9')
	return (1);
    return (0);
}


/** islower(c) returns true if c is lower case */
int islower (c)
     int             c;
{
    if (c >= 'a' && c <= 'z')
	return (1);
    return (0);
}


/** isupper(c) returns true if c is upper case */
int isupper (c)
     int             c;
{
    if (c >= 'A' && c <= 'Z')
	return (1);
    return (0);
}
#endif
/*************************************************************
 *  int vsprintf(d,s,ap)
 */
int 
vsprintf (char *d, const char *s, const char *ap)
{
    const char     *t;
    char           *p, *dst, tmp[40];
    unsigned int    n;
    int             fmt, trunc, haddot, width, base, longlong;

    dst = d;
    for (; *s;) {
	if (*s == '%') {
	    s++;
	    fmt = FMT_RJUST;
	    width = trunc = haddot = longlong = 0;
	    for (; *s; s++) {
		if (strchr ("dobxXulscefg%", *s))
		    break;
		else if (*s == '-')
		    fmt = FMT_LJUST;
		else if (*s == '0')
		    fmt = FMT_RJUST0;
		else if (*s == '~')
		    fmt = FMT_CENTER;
		else if (*s == '*') {
		    if (haddot)
		    {
			trunc = *(int *)ap;
		    	ap += sizeof(int);
		    }
		    else
		    {
			width = *(int *)ap;
		    	ap += sizeof(int);
		    }
		} else if (*s >= '1' && *s <= '9') {
		    for (t = s; isdigit (*s); s++);
		    strncpy (tmp, t, s - t);
		    tmp[s - t] = '\0';
		    atob (&n, tmp, 10);
		    if (haddot)
			trunc = n;
		    else
			width = n;
		    s--;
		} else if (*s == '.')
		    haddot = 1;
	    }
	    if (*s == '%') {
		*d++ = '%';
		*d = 0;
	    } else if (*s == 's') {
		p = *(char **)ap;
		ap += sizeof(char *);

		if (p)
		    strcpy (d, p);
		else
		    strcpy (d, "(null)");
	    } else if (*s == 'c') {
		n = *(int *)ap;
		ap += sizeof(int);

		*d = n;
		d[1] = 0;
	    } else {
		if (*s == 'l') {
		    if (*++s == 'l') {
			longlong = 1;
			++s;
		    }
		}
		if (strchr ("dobxXu", *s)) {
		    if (*s == 'd')
			base = -10;
		    else if (*s == 'u')
			base = 10;
		    else if (*s == 'x' || *s == 'X')
			base = 16;
		    else if (*s == 'o')
			base = 8;
		    else if (*s == 'b')
			base = 2;

		    btoa (d, *(int *)ap, base);
		    ap += sizeof(int);

		    if (*s == 'X')
			strtoupper (d);
		}
	    }
	    if (trunc)
		d[trunc] = 0;
	    if (width)
		str_fmt (d, width, fmt);
	    for (; *d; d++);
	    s++;
	} else
	    *d++ = *s++;
    }
    *d = 0;
    return (d - dst);
}

