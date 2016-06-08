CROSS_COMPILE=mipsel-linux-
CC = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
AR = $(CROSS_COMPILE)ar -r
LD = $(CROSS_COMPILE)ld
AFLAGS = -G 0  -Os -Wall -Wstrict-prototypes -fpic -fno-builtin -mabicalls -pipe -mips2 -nostdlib -nostdinc -msoft-float -mlong-calls -EL
CPU_FREQ_MHZ = 250

LWIP = 0
MODBUS = 1

export CC LD OBJCOPY OBJDUMP AFLAGS CPU_FREQ_MHZ LWIP MODBUS

SUBDIR := lib canopen modules
ifeq ($(LWIP),1)
SUBDIR += lwip
endif

ifeq ($(MODBUS),1)
SUBDIR += modbus
endif

SUBDIR += app

all: subdir

subdir:
	for dir in $(SUBDIR); do \
		$(MAKE) -C $$dir || exit "$$?"; \
	done

.PHONY: clean

clean:
	for dir in $(SUBDIR); do \
		$(MAKE) -C $$dir clean ; \
	done

