AM_CPPFLAGS = -I$(top_builddir)/release

EXTRA_PROGRAMS = spanish
EXTRA_DIST = spanish.c

examples: $(EXTRA_PROGRAMS)

$(top_srcdir)/src/beguile.h: .FORCE
	$(MAKE) -C $(top_builddir)/src

CLEANFILES = spanish

.FORCE:
.PHONY: examples
