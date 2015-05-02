#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([Beguile], [0.2.0], [superruzafa@gmail.com], [beguile], [https://github.com/superruzafa/beguile.git])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/package.h.in])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_ARG_WITH([tests], AS_HELP_STRING([--without-tests], [Disable tests]))
AS_IF([test "x$with_tests" != "xno"], [
    PKG_CHECK_MODULES([CHECK], [check], [], [AC_MSG_ERROR([No package 'check' found. Install check package or try ./configure --without-tests])])
])

DATE=`date +"%Y-%m-%d %H:%M:%S"`
AC_SUBST([DATE])

# Beguile modules
MODULES="info.h header.h package.h util.h style.h signals.h core.h options.h tags.h"

AC_ARG_ENABLE([english], AS_HELP_STRING([--disable-english], [Disable english language]))
AS_IF([test "x$enable_english" != "xno"], [
    MODULES="$MODULES lang_en.h"
    SUPPORT_EN=x
], SUPPORT_EN="x")
AC_SUBST([SUPPORT_EN])

AC_ARG_ENABLE([spanish], AS_HELP_STRING([--enable-spanish], [Enable spanish language]))
AS_IF([test "x$enable_spanish" = "xyes"], [
    MODULES="$MODULES lang_es.h"
    SUPPORT_ES=x
], [SUPPORT_ES=" "])
AC_SUBST([SUPPORT_ES])

MODULES="$MODULES footer.h"
AC_SUBST([MODULES])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/package.h
    src/info.h
    tests/Makefile
    examples/Makefile
    examples/stack/Makefile
    examples/hooks/Makefile
    examples/i18n/Makefile
])
AC_OUTPUT
