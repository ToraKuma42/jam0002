prefix= /usr/local
DIRS = src

.PHONY: install

all:
	for i in $(DIRS); \
	do \
	  $(MAKE) -C $$i all || exit 1 ; \
	done

clean:
	for i in $(DIRS); \
	do \
	  $(MAKE) -C $$i clean || exit 1 ; \
	done

install: serow
	install -m 0755 $(DIRS)/src $(prefix)/bin


