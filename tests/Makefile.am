AM_CPPFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@

TESTS = backgrounds hooks

check_PROGRAMS = backgrounds hooks

backgrounds_SOURCES = backgrounds.c
backgrounds_LDADD = @CHECK_LIBS@

hooks_SOURCES = hooks.c
hooks_LDADD = @CHECK_LIBS@

$(top_builddir)/src/beguile.h: .FORCE
	$(MAKE) -C $(top_builddir)/src

.FORCE:
