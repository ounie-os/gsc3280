VPATH = ../common ../lib/ ../canopen/user ../canopen/src ../canopen/bsp ../modules/can ../modules/gpio ../modules/timer ../modules/eth ../modules/uart ../lwip ../modbus/src
LDFLAGS = -G 0  -static -T ../common/ld.script

TARGET = app
OBJS =  start.S start.c cache.S cache.c eth-test.c timer_gsc3280.o can_gsc3280.o gpio_gsc3280.o eth_gsc3280.o uart_gsc3280.o libcanopenuser.o libcanopenbsp.o libcanfestival.o libc.a

ifeq ($(LWIP),1)
OBJS += lwip.o
endif
ifeq ($(MODBUS),1)
OBJS += modbus.o
endif

INCLUDES = -I./ -I../include -I../canopen/inc -I../canopen/user -I../include/modules -I../lwip/include -I../lwip/include/ipv4 -I../modbus/port -I../modbus/src/include

$(TARGET): $(OBJS)
	@echo " "
	@echo "*********************************************"
	@echo "**Compiling test app"
	@echo "*********************************************"
	$(CC) $(LDFLAGS) $(AFLAGS)  $(INCLUDES) $^ -o $@
	$(OBJCOPY) -O binary $@  $(TARGET).bin
	#$(OBJDUMP) -D  $(TARGET) > $(TARGET).s
	#mv $@ $@.elf
	rm -rf $@


clean:
	rm -rf $(TARGET).elf $(TARGET).s  $(TARGET).bin $(TARGET)

