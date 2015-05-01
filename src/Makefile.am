BUILT_SOURCES = beguile.h
CLEANFILES = package.h info.h
DISTCLEANFILES = beguile.h
EXTRA_DIST = beguile.h package.h info.h core.h footer.h header.h lang_en.h lang_es.h signals.h style.h util.h

beguile.h: $(MODULES)
	cat $^ > $@
