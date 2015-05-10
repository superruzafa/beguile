AM_CPPFLAGS = -I$(top_builddir)/release

EXTRA_LIBRARIES = libstack.a
libstack_a_SOURCES = stack.c

EXTRA_PROGRAMS = stack_feature
EXTRA_DIST = stack_context.c
stack_feature_SOURCES =  stack_feature.c
stack_feature_LDADD = libstack.a

examples: stack_feature

$(top_srcdir)/src/beguile.h: .FORCE
	$(MAKE) -C $(top_builddir)/src

CLEANFILES = libstack.a stack_feature

.FORCE:
.PHONY: examples
