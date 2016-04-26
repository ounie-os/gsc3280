CROSS_COMPILE=mipsel-linux-
CC = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
AR = $(CROSS_COMPILE)ar -r
LD = $(CROSS_COMPILE)ld
AFLAGS = -G 0  -Os -Wall -Wstrict-prototypes -fpic -fno-builtin -mabicalls -pipe -mips2 -nostdlib -nostdinc -msoft-float -mlong-calls -EL
CPU_FREQ_MHZ = 250
export CC LD OBJCOPY OBJDUMP AFLAGS CPU_FREQ_MHZ

ALL = lib_gsc3280 can_open modules app

#.PHONY: all
all: $(ALL)

can_open:
	cd canopen/ && make

lib_gsc3280:
	cd lib/ && make

app: lib_gsc3280
	cd app/ && make

modules: lib_gsc3280
	cd modules/ && make

clean_lib:
	cd lib/ && make clean

clean_canopen:
	cd canopen/ && make clean

clean_app:
	cd app/ && make clean

clean_modules:
	cd modules/ && make clean

.PHONY: clean
clean: clean_canopen clean_lib clean_modules clean_app

