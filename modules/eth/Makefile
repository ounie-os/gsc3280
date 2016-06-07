OPT_CFLAGS = -O2
CFLAGS = $(OPT_CFLAGS)
PROG_CFLAGS =  -D_GNU_SOURCE -D_REENTRANT -nostdlib -fno-builtin -DCPU_FREQ_MHZ=$(CPU_FREQ_MHZ)
TARGET = eth_gsc3280

ifeq ($(LWIP),1)
PROGDEFINES = -DLWIP
endif

INCLUDES = -I./ -I../../include -I../../include/modules -I../../lwip/include -I../../lwip/include/ipv4

OBJS = miiphyutil.o gsc3280_mac.o

all: $(TARGET).o
	
$(TARGET).o: $(OBJS)
	$(LD) -r $(OBJS) -o $@

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
	rm -f $(OBJS) $(TARGET).o