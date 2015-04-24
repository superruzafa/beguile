AM_CPPFLAGS = -I$(top_srcdir)/src

TESTS = test feature

check_PROGRAMS = test feature

$(top_srcdir)/src/beguile.h: .FORCE
	$(MAKE) -C $(top_srcdir)/src

.FORCE:
