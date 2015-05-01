#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([Beguile], [0.2.0], [superruzafa@gmail.com], [beguile])
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

# Beguile modules
MODULES="header.h package.h util.h style.h signals.h core.h"

AC_ARG_ENABLE([english], AS_HELP_STRING([--disable-english], [Disable english language]))
AS_IF([test "x$enable_english" != "xno"], [
    MODULES="$MODULES lang_en.h"
])

MODULES="$MODULES footer.h"
AC_SUBST([MODULES])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/package.h
    tests/Makefile
    examples/Makefile
    examples/stack/Makefile
])
AC_OUTPUT
