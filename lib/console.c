#include <stdio.h>
#include <console.h>
static Console *console_table[CONSOLE]__attribute__((section(".data")))={NULL,NULL,NULL,} ;
static int count = 0;

void register_console(Console *csl)
{
    int i = 0;
    for (;console_table[i] != NULL && i < CONSOLE;i++);
    if(i==CONSOLE){
    	printf("register console, Out of range!!!\n");
	return;
    }
    console_table[i] = csl;
}

void console_putc(char c)
{
    int i = 0;
    for (;console_table[i] != NULL && i < CONSOLE;i++)
	if (console_table[i]->putc)
	    console_table[i]->putc(c);
}

void console_puts(char *buf)
{
    int i = 0;
    for (;console_table[i] != NULL && i< CONSOLE;i++)
	if (console_table[i]->puts)
	    console_table[i]->puts(buf);
}

void console_flush(char sel)
{
    int i = 0;
    for (;console_table[i] != NULL && i< CONSOLE;i++)
	if (console_table[i]->flush)
	    console_table[i]->flush(sel);
}

void console_getc(char *buf)
{
    int i = 0;
    u8 timeout = 0;
    while (1)
    {
	if (console_table[i] == NULL || console_table[i]->getc == NULL)
	{
	    i++;
	    if (i == CONSOLE)
		i = 0;
	    continue;
	}
	timeout = console_table[i]->getc(buf);
	if (timeout)
	{
	    i++;
	    if (i == CONSOLE)
		i = 0;
	    continue;
	}
	if (*buf == 0)
	    continue;
	if (*buf == '\b')
	{
	    if (count <= 0)
		break;
	    count--;
	    console_putc(*buf);
	    console_putc(' ');
	    console_putc(*buf);
	    break;
	}

	count++;
	console_putc(*buf);
	break;
    }
}

void console_gets(char *buf)
{
    int i = 0;

    count = 0;
    while (1)
    {
	console_getc(buf+i);
	/* direction array */
	if (buf[i] == '\e')
	{
	    buf[i] = 0;
	    console_getc(buf+i);
	    if (buf[i] == '[')
	    {
		console_getc(buf+i);
		switch (buf[i])
		{
		    case 'A':
		    case 'B':
		    case 'C':
		    case 'D':
			break;
		}
	    }
	    continue;
	}
	if (buf[i] == '\n')
	    break;
	if (buf[i] == '\r')
	{
	    console_putc('\n');
	    break;
	}
	if (buf[i] == '\b')
	{
	    if (i)
	    {
		i--;
		continue;
	    }
	    else
		continue;
	}
	i++;
    }

    buf[i] = 0;
    console_flush(IN);
}
