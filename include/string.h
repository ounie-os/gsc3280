/* $Id: string.h;
char v 1.1.1.1 2003/04/22 01:33:46 wolfhe Exp $ */
#ifndef _STRING_
#define _STRING_
/*
char *strcat();
char *strncat();
char *strchr();
char *strncpy();
char *cc2str();
char *rindex();
char *strcpy();
char *strichr();
char *strdchr();
char *strposn();
char *getword();
char *index();
char *strset();
char *strrset();
char *strrchr();
char *strbalp();
char *strrpset();
char *strpbrk();
char *strtok();
int strequ();
char strlequ();
char strlen();
char strpat();
*/

/* definitions for fmt parameter of str_fmt(p;
char width;
char fmt) */
#define FMT_RJUST 0
#define FMT_LJUST 1
#define FMT_RJUST0 2
#define FMT_CENTER 3

#endif /* _STRING_ */
