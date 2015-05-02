SUBDIRS = stack i18n hooks

examples:
	for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir $@; \
	done

.PHONY: examples
