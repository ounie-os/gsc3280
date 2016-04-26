CROSS_COMPILE = mipsel-linux-
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar -r
INCLUDES = -I ../include -I .
AFLAGS = -G 0  -O2 -Wall -Wstrict-prototypes -fpic -fno-builtin -mabicalls -pipe -mips2 -nostdlib -nostdinc -mlong-calls $(INCLUDES) -DCPU_FREQ_MHZ=$(CPU_FREQ_MHZ)
BUILDOBJ=.

LIBS = $(BUILDOBJ)/libc.a
OBJS = $(BUILDOBJ)/genex.o $(BUILDOBJ)/irq.o $(BUILDOBJ)/malloc.o $(BUILDOBJ)/memcpy.o $(BUILDOBJ)/memcmp.o \
       $(BUILDOBJ)/panic.o $(BUILDOBJ)/dump.o\
       $(BUILDOBJ)/string.o $(BUILDOBJ)/printf.o $(BUILDOBJ)/vsprintf.o $(BUILDOBJ)/sprintf.o $(BUILDOBJ)/atob.o $(BUILDOBJ)/console.o\
       $(BUILDOBJ)/argvize.o $(BUILDOBJ)/wait.o $(BUILDOBJ)/time.o $(BUILDOBJ)/ctype.o\

all: $(LIBS)
$(LIBS):$(OBJS)
	$(AR) $@ $^
$(BUILDOBJ)/genex.o:genex.S
	$(CC) $(AFLAGS) -D__ASSEMBLY__ -c $< -o $@
$(BUILDOBJ)/irq.o:irq.c
	$(CC) $(AFLAGS) -c $< -o $@
$(BUILDOBJ)/malloc.o:malloc.c
	$(CC) $(AFLAGS) -c $< -o $@
$(BUILDOBJ)/memcpy.o:memcpy.c
	$(CC) $(AFLAGS) -c $< -o $@
$(BUILDOBJ)/memcmp.o:memcmp.c
	$(CC) $(AFLAGS) -c $< -o $@
$(BUILDOBJ)/memset.o:memset.S
	$(CC) $(AFLAGS) -D__ASSEMBLY__ -c $< -o $@
$(BUILDOBJ)/panic.o:panic.c
	$(CC) $(AFLAGS) -c $< -o $@
$(BUILDOBJ)/dump.o:dump.c
	$(CC) $(AFLAGS) -c $< -o $@
$(BUILDOBJ)/string.o:string.c
	$(CC) $(AFLAGS) -c $< -o $@
$(BUILDOBJ)/printf.o:printf.c
	$(CC) $(AFLAGS) -c $< -o $@
$(BUILDOBJ)/vsprintf.o:vsprintf.c
	$(CC) $(AFLAGS) -c $< -o $@
$(BUILDOBJ)/sprintf.o:sprintf.c
	$(CC) $(AFLAGS) -c $< -o $@
$(BUILDOBJ)/atob.o:atob.c
	$(CC) $(AFLAGS) -c $< -o $@
$(BUILDOBJ)/argvize.o:argvize.c
	$(CC) $(AFLAGS) -c $< -o $@
$(BUILDOBJ)/wait.o:wait.c
	$(CC) $(AFLAGS) -c $< -o $@
$(BUILDOBJ)/console.o:console.c
	$(CC) $(AFLAGS) -c $< -o $@
$(BUILDOBJ)/time.o:time.c
	$(CC) $(AFLAGS) -c $< -o $@
$(BUILDOBJ)/ctype.o:ctype.c
	$(CC) $(AFLAGS) -c $< -o $@
clean:
	rm -rf $(LIBS) $(OBJS)

