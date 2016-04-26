#ifndef _CONSOLE_H_
#define _CONSOLE_H_
#include <types.h>
#define CONSOLE 10
#define IN  0
#define OUT 1

typedef struct Console
{
    char name[20];
    void (*putc)(char);
    void (*puts)(char *);
    u8 (*getc)(char *);
    void (*gets)(char *);
	void (*flush)(u8);
}Console;
extern void register_console(Console *cls);
extern void console_putc(char c);
extern void console_puts(char *buf);
extern void console_getc(char *buf);
extern void console_gets(char *buf);
extern void console_flush(char sel);
#endif
