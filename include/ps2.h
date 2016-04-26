#ifndef __PS2_H
#define __PS2_H

#define PS2_0_BASE     0xbc106000
#define PS2_0_IBUF     PS2_0_BASE+0x0
#define PS2_0_OBUF     PS2_0_BASE+0x4
#define PS2_0_SR       PS2_0_BASE+0x8
#define PS2_0_CR       PS2_0_BASE+0xc
#define PS2_0_CPSR	   PS2_0_BASE+0x10
#define PS2_0_DVR	   PS2_0_BASE+0x14

unsigned char keyboard_read_status();
unsigned char keyboard_read_input();
int ps2_init();
int ps2_keyboard_test();

#endif
