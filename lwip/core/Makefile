PROG_CFLAGS =  -D_GNU_SOURCE -D_REENTRANT -nostdlib -fno-builtin
INCLUDES = -I../include -I../../include -I../include/ipv4
CFLAGS = -O2
TARGET = lwipcore
SUB_TARGET = core

OBJS = def.o init.o mem.o memp.o netif.o pbuf.o raw.o stats.o sys.o timers.o tcp.o tcp_in.o tcp_out.o udp.o dhcp.o dns.o

all: core_src ipv4_src
	$(LD) -r $(SUB_TARGET).o ./ipv4/lwipipv4.o -o $(TARGET).o

ipv4_src:
	$(MAKE) -C ipv4
	
core_src: $(SUB_TARGET).o

$(SUB_TARGET).o: $(OBJS)
	$(LD) -r $(OBJS) -o $@
	
%.o: %.c
	@echo " "
	@echo "*********************************************"
	@echo "**Compiling $< -> $@"
	@echo "*********************************************"
	$(CC) $(CFLAGS) $(PROG_CFLAGS) ${AFLAGS} $(INCLUDES) -o $@ -c $<

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET).* *.o
	$(MAKE) -C ipv4 clean
