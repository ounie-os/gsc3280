SUBDIR := core netif user_config

SUBOBJS = ./core/lwipcore.o ./netif/lnetif.o ./user_config/netconfig.o
TARGET = lwip.o

all: subdir
	$(LD) -r $(SUBOBJS) -o $(TARGET)

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

