SUBDIR := can gpio timer eth

all: subdir

subdir:
	for dir in $(SUBDIR); do \
		$(MAKE) -C $$dir ; \
	done

.PHONY: clean

clean:
	for dir in $(SUBDIR); do \
		$(MAKE) -C $$dir clean ; \
	done
