SUBDIRS = src tests examples release

examples:
	$(MAKE) -C release
	$(MAKE) -C $@ $@

.PHONY: examples
