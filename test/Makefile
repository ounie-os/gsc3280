VPATH = ../common ../lib/ ../canopen/user ../canopen/src ../canopen/bsp ../modules/can ../modules/gpio ../modules/timer ../modules/eth ../lwip
LDFLAGS = -G 0  -static -T ../common/ld.script

TARGET = app
OBJS =  start.S start.c eth-test.c timer_gsc3280.o can_gsc3280.o gpio_gsc3280.o eth_gsc3280.o libcanopenuser.o libcanopenbsp.o libcanfestival.o lwip.o libc.a
INCLUDES = -I./ -I../include -I../canopen/inc -I../canopen/user -I../modules/can -I../modules/timer -I../modules/gpio -I../modules/eth -I../lwip/include -I../lwip/include/ipv4

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

