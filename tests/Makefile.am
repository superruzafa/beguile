AM_CPPFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LIBS = @CHECK_LIBS@

TESTS = asserts backgrounds hooks fork tags_

check_PROGRAMS = asserts backgrounds hooks fork tags_

tags__SOURCES = tags.c

$(top_builddir)/src/beguile.h: .FORCE
	$(MAKE) -C $(top_builddir)/src

.FORCE:
