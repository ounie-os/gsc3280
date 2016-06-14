OPT_CFLAGS = -O2
CFLAGS = $(OPT_CFLAGS)
PROG_CFLAGS =  -D_GNU_SOURCE -D_REENTRANT -nostdlib -fno-builtin
TARGET = mb_port

INCLUDES = -I./ -I../src/include -I../../include -I../../include/modules

OBJS = portevent.o portserial.o porttimer.o porttcp.o

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