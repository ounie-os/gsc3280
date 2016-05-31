PROG_CFLAGS =  -D_GNU_SOURCE -D_REENTRANT -nostdlib -fno-builtin
INCLUDES = -I../include -I../include/ipv4 -I../include/lwip -I../../include
CFLAGS = -O2
TARGET = lwipapi

OBJS = netbuf.o netdb.o netifapi.o sockets.o tcpip.o api_lib.o api_msg.o err.o

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
