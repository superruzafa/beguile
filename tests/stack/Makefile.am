AM_CPPFLAGS = -I$(top_srcdir)/src

TESTS = stack

check_PROGRAMS = stack

stack_SOURCES = stack.c stack_feature.c

$(top_srcdir)/src/beguile.h: .FORCE
	$(MAKE) -C $(top_srcdir)/src

.FORCE:
