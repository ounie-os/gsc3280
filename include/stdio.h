#ifndef STDIO
#define STDIO

#include <linux/ctype.h>

#define NULL (void *)0
#define WARNING(msg) {\
    bios_msg("WARNING:");\
    bios_msg(msg);}

#ifdef  DEBUG
#define debug(fmt,args...)      printf (fmt ,##args)
#define debugX(level,fmt,args...) if (DEBUG>=level) printf(fmt,##args);
#else
#define debug(fmt,args...)
#define debugX(level,fmt,args...)
#endif  /* DEBUG */

/* definitions for fmt parameter of str_fmt(p,width,fmt) */
#define FMT_RJUST 0
#define FMT_LJUST 1
#define FMT_RJUST0 2
#define FMT_CENTER 3


extern void memcpy(void *to, void *from, int size);
extern int memcmp(void *to, void *from, int size);
extern void memset(void *to, char c, int len);
extern void *malloc(int size);
extern void panic(char *msg);
extern void bios_msg(char *msg);
extern int strlen(char *str);
//extern int strlen(char * s)
extern void strcpy(char *to, char *from);
extern int strcmp(char *to, char *from);
//extern strcmp(char * cs,char * ct)
extern void bts(unsigned char *c, unsigned char b);
extern int stx(unsigned int *result, char *buf);
extern void str_fmt (char *p, int size, int fmt);
extern char *strcat (char *dst, char *src);
extern char *strchr (char *p, char c);
extern char *strichr (char *p, int c);
extern char *strncpy (char *dst,char *src,int n);
//extern int toupper (int c);
extern void strtoupper (char *p);
extern char *strblank(char *buf, int num);
extern char *strunblank(char *buf, int num);

int strstr(char *s1, char *s2);
#if 0
int isdigit (int c);
int islower (int c);
int isupper (int c);
#endif
 int vprintf (const char *fmt, const char * ap);
 int printf (const char *fmt, ...);
int vsprintf (char *d, const char *s, const char *ap);

extern int atob (unsigned int*, char*, int);
char *btoa (char*, unsigned int, int);
extern int gethex (unsigned long*, char*, int);

extern void udelay(int t);
extern void mdelay(int t);

extern void wait(int t);
extern void  *malloc(int size);
extern void free(void *base);
static inline void puts(const char *s)
{
        printf("%s",s);
}
extern unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base);
#endif /* STDIO */
