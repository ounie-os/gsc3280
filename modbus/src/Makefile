PROG_CFLAGS =  -D_GNU_SOURCE -D_REENTRANT -nostdlib -fno-builtin
INCLUDES = -I./include -I../port -I./rtu -I./tcp -I../../include
CFLAGS = -O2
TARGET = modbus.o
OBJS = mb.o
SUBOBJS = ./rtu/mb_rtu.o ./functions/mb_func.o ../port/mb_port.o

SUBDIR := rtu functions

all: subdir $(OBJS)
	$(LD) -r $(SUBOBJS) $(OBJS) -o $(TARGET)

%.o: %.c
	@echo " "
	@echo "*********************************************"
	@echo "**Compiling $< -> $@"
	@echo "*********************************************"
	$(CC) $(CFLAGS) $(PROG_CFLAGS) ${PROGDEFINES} $(INCLUDES) -o $@ -c $<

subdir:
	for dir in $(SUBDIR); do \
		$(MAKE) -C $$dir || exit "$$?"; \
	done

.PHONY: clean

clean:
	for dir in $(SUBDIR); do \
		$(MAKE) -C $$dir clean ; \
	done
	rm -rf *.o
