AM_CPPFLAGS = -I$(top_builddir)/release @CHECK_CFLAGS@
LIBS = @CHECK_LIBS@
DISTCLEANFILES=asserts.c tags.c

TESTS = asserts backgrounds hooks fork options tags_

check_PROGRAMS = asserts backgrounds hooks fork options tags_

tags__SOURCES = tags.c

%.c: %.erb
	erb -T - $^ > $@

$(top_builddir)/src/beguile.h: .FORCE
	$(MAKE) -C $(top_builddir)/src

.FORCE:
