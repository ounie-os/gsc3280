VPATH = ../common ../lib/ ../canopen/user ../canopen/src ../canopen/bsp
LDFLAGS = -G 0  -static -T ../common/ld.script

TARGET = app
OBJS =  start.S start.c timer_gsc3280.c can_gsc3280.c main.c libcanopenuser.o libcanopenbsp.o libcanfestival.o libc.a
INCLUDES = -I ../include -I ../canopen/inc -I ../canopen/user

AFLAGS += -DUSE_CAN0

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(AFLAGS)  $(INCLUDES) $^ -o $@
	$(OBJCOPY) -O binary $@  $(TARGET).bin
	#$(OBJDUMP) -D  $(TARGET) > $(TARGET).s
	#mv $@ $@.elf
	rm -rf $@


clean:
	rm -rf $(TARGET).elf $(TARGET).s  $(TARGET).bin $(TARGET)

