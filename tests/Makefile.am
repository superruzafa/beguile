AM_CPPFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LIBS = @CHECK_LIBS@
TESTS = asserts backgrounds hooks fork options

check_PROGRAMS = asserts backgrounds hooks fork options

$(top_builddir)/src/beguile.h: .FORCE
	$(MAKE) -C $(top_builddir)/src

.FORCE:
