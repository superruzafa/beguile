AM_CPPFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@

TESTS = asserts backgrounds hooks fork

check_PROGRAMS = asserts backgrounds hooks fork

asserts_SOURCES = asserts.c
asserts_LDADD = @CHECK_LIBS@

backgrounds_SOURCES = backgrounds.c
backgrounds_LDADD = @CHECK_LIBS@

hooks_SOURCES = hooks.c
hooks_LDADD = @CHECK_LIBS@

fork_SOURCES = fork.c
fork_LDADD = @CHECK_LIBS@

$(top_builddir)/src/beguile.h: .FORCE
	$(MAKE) -C $(top_builddir)/src

.FORCE:
