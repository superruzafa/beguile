DISTCLEANFILES = beguile.h beguile_min.h
BUILT_SOURCES = beguile.h beguile_min.h

beguile.h: .FORCE
	rm -rf $@
	for m in $(MODULES_FULL); do \
		cat $(top_builddir)/src/$$m >> $@; \
	done

beguile_min.h: .FORCE
	rm -rf $@
	for m in $(MODULES_MIN); do \
		cat $(top_builddir)/src/$$m >> $@; \
	done

.FORCE:
