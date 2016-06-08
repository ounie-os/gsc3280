OPT_CFLAGS = -O2
CFLAGS = $(OPT_CFLAGS)
PROG_CFLAGS =  -D_GNU_SOURCE -D_REENTRANT -nostdlib -fno-builtin
TARGET = mb_rtu

INCLUDES = -I./ -I../include -I../../port -I../../../include

OBJS = mbcrc.o mbrtu.o

all: $(TARGET).o

$(TARGET).o: $(OBJS)
	$(LD) -r $(OBJS) -o $@

%.o: %.c
	@echo " "
	@echo "*********************************************"
	@echo "**Compiling $< -> $@"
	@echo "*********************************************"
	$(CC) $(CFLAGS) $(PROG_CFLAGS) ${PROGDEFINES} $(INCLUDES) -o $@ -c $<

.PHONY: clean
clean:
	rm -f *.o