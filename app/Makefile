VPATH = ../common ../lib/ ../canopen/user ../canopen/src ../canopen/bsp ../modules/can ../modules/gpio ../modules/timer
LDFLAGS = -G 0  -static -T ../common/ld.script

TARGET = app
OBJS =  start.S start.c task.c main.c timer_gsc3280.o can_gsc3280.o libcanopenuser.o libcanopenbsp.o libcanfestival.o libc.a
INCLUDES = -I ../include -I ../canopen/inc -I ../canopen/user -I../modules/can -I ../modules/timer -I../modules/gpio

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(AFLAGS)  $(INCLUDES) $^ -o $@
	$(OBJCOPY) -O binary $@  $(TARGET).bin
	#$(OBJDUMP) -D  $(TARGET) > $(TARGET).s
	#mv $@ $@.elf
	rm -rf $@


clean:
	rm -rf $(TARGET).elf $(TARGET).s  $(TARGET).bin $(TARGET)

