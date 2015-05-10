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
AC_CHECK_PROG([ERB], [erb], [yes], [no])

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_ARG_WITH([tests], AS_HELP_STRING([--without-tests], [Disable tests]))
AS_IF([test "x$with_tests" != "xno"], [
    PKG_CHECK_MODULES([CHECK], [check], [], [AC_MSG_ERROR([No package 'check' found. Install `check` package or try ./configure --without-tests])])
    AS_IF([test "x$ERB" != "xyes"], [AC_MSG_ERROR([No program 'erb' found. Install `erb` program or try ./configure --without-tests])])
])

# Beguile modules
MODULES="info.h header.h package.h util.h style.h signals.h core.h"
MODULES_FULL=$MODULES
MODULES_MIN=$MODULES

AC_ARG_ENABLE([options], AS_HELP_STRING([--disable-options], [Disable command line options]))
AS_IF([test "x$enable_options" != "xno"], [
    MODULES="$MODULES options.h"
])
AC_SUBST([SUPPORT_OPTIONS])
MODULES_FULL="$MODULES_FULL options.h"

AC_ARG_ENABLE([tags], AS_HELP_STRING([--disable-tags], [Disable tags]))
AS_IF([test "x$enable_tags" != "xno"], [
    MODULES="$MODULES tags.h"
])
MODULES_FULL="$MODULES_FULL tags.h"

AC_ARG_ENABLE([english], AS_HELP_STRING([--disable-english], [Disable english language]))
AS_IF([test "x$enable_english" != "xno"], [
    MODULES="$MODULES lang_en.h"
])
MODULES_FULL="$MODULES_FULL lang_en.h"
MODULES_MIN="$MODULES_MIN lang_en.h"

AC_ARG_ENABLE([spanish], AS_HELP_STRING([--enable-spanish], [Enable spanish language]))
AS_IF([test "x$enable_spanish" = "xyes"], [
    MODULES="$MODULES lang_es.h"
])
MODULES_FULL="$MODULES_FULL lang_es.h"

MODULES="$MODULES footer.h"
MODULES_FULL="$MODULES_FULL footer.h"
MODULES_MIN="$MODULES_MIN footer.h"
AC_SUBST([MODULES])
AC_SUBST([MODULES_FULL])
AC_SUBST([MODULES_MIN])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/package.h
    src/info.h
    tests/Makefile
    release/Makefile
    examples/Makefile
    examples/stack/Makefile
    examples/hooks/Makefile
    examples/i18n/Makefile
])
AC_OUTPUT
