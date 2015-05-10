AM_CPPFLAGS = -I$(top_builddir)/release
EXTRA_PROGRAMS = hooks
EXTRA_DIST = hooks.c
CLEANFILES = hooks

examples: $(EXTRA_PROGRAMS)

$(top_srcdir)/src/beguile.h: .FORCE
	$(MAKE) -C $(top_builddir)/src

.FORCE:
.PHONY: examples
