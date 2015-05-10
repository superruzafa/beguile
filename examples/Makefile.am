AM_CPPFLAGS = -I$(top_builddir)/release
EXTRA_PROGRAMS = hooks/hooks i18n/spanish stack/stack_feature tags/tags_
EXTRA_LIBRARIES = stack/libstack.a
EXTRA_DIST = stack/stack_context.c
CLEANFILES = hooks/hooks i18n/spanish stack/libstack.a stack/stack_feature tags/tags_

stack_libstack_a_SOURCES = stack/stack.c
stack_stack_feature_LDADD =  stack/libstack.a
examples: $(EXTRA_PROGRAMS)
