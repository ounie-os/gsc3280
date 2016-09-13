OPT_CFLAGS = -O2
CFLAGS = $(OPT_CFLAGS)
PROG_CFLAGS =  -D_GNU_SOURCE -D_REENTRANT -nostdlib -fno-builtin
TARGET = dma_gsc3280

INCLUDES = -I./ -I../../include -I../../include/modules -I../../canopen/inc

OBJS = $(TARGET).o

all: $(TARGET).o

$(TARGET).a: $(OBJS)
	$(CROSS_COMPILE)ar rc $@ $(OBJS)
	$(CROSS_COMPILE)ranlib $@

%.o: %.c
	@echo " "
	@echo "*********************************************"
	@echo "**Compiling $< -> $@"
	@echo "*********************************************"
	$(CC) $(CFLAGS) $(PROG_CFLAGS) ${PROGDEFINES} $(INCLUDES) -o $@ -c $<

.PHONY: clean
clean:
	rm -f $(OBJS)