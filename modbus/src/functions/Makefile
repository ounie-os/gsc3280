OPT_CFLAGS = -O2
CFLAGS = $(OPT_CFLAGS)
PROG_CFLAGS =  -D_GNU_SOURCE -D_REENTRANT -nostdlib -fno-builtin
TARGET = mb_func

INCLUDES = -I./ -I../../../include -I../include -I../../port 

OBJS = mbfunccoils.o mbfuncdiag.o mbfuncdisc.o mbfuncholding.o mbfuncinput.o mbfuncother.o mbutils.o modbusCB.o

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