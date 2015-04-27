AM_CPPFLAGS = -I$(top_builddir)/src

TESTS = backgrounds hooks

check_PROGRAMS = backgrounds hooks

$(top_builddir)/src/beguile.h: .FORCE
	$(MAKE) -C $(top_builddir)/src

.FORCE:
