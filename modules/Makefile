SUBDIR := can gpio timer eth uart emi dma

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
