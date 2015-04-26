AM_CPPFLAGS = -I$(top_builddir)/src

TESTS = backgrounds hooks signals

check_PROGRAMS = backgrounds hooks signals

$(top_builddir)/src/beguile.h: .FORCE
	$(MAKE) -C $(top_builddir)/src

.FORCE:
