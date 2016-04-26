ALL = canopen_src canopen_bsp canopen_user

all: $(ALL)

canopen_src:
	cd src/ && make

canopen_bsp:
	cd bsp/ && make

canopen_user:
	cd user/ && make

clean_canopen_src:
	cd src/ && make clean

clean_canopen_bsp:
	cd bsp/ && make clean

clean_canopen_user:
	cd user/ && make clean

.PHONY: clean
clean: clean_canopen_src clean_canopen_bsp clean_canopen_user

