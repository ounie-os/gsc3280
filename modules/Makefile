ALL = can_module gpio_module timer_module

all: $(ALL)

can_module:
	cd can/ && make

gpio_module:
	cd gpio/ && make

timer_module:
	cd timer/ && make

clean_can_module:
	cd can/ && make clean

clean_gpio_module:
	cd gpio/ && make clean

clean_timer_module:
	cd timer/ && make clean

.PHONY: clean
clean: clean_can_module clean_gpio_module clean_timer_module

