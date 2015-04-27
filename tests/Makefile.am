AM_CPPFLAGS = -I$(top_builddir)/src

TESTS = backgrounds

check_PROGRAMS = backgrounds

$(top_builddir)/src/beguile.h: .FORCE
	$(MAKE) -C $(top_builddir)/src

.FORCE:
