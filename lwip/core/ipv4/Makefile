PROG_CFLAGS =  -D_GNU_SOURCE -D_REENTRANT -nostdlib -fno-builtin
INCLUDES = -I../../include -I../../include/ipv4 -I../../../include
CFLAGS = -O2
TARGET = lwipipv4

OBJS = ip.o ip_addr.o ip_frag.o autoip.o icmp.o igmp.o inet.o inet_chksum.o

all: $(TARGET).o

$(TARGET).o: $(OBJS)
	$(LD) -r $(OBJS) -o $@
	
%.o: %.c
	@echo " "
	@echo "*********************************************"
	@echo "**Compiling $< -> $@"
	@echo "*********************************************"
	$(CC) $(CFLAGS) $(PROG_CFLAGS) ${AFLAGS} $(INCLUDES) -o $@ -c $<

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET).*
