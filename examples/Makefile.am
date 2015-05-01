SUBDIRS = stack i18n

examples:
	for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir $@; \
	done

.PHONY: examples
