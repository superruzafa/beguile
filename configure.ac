#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([Beguile], [0.1.0], [superruzafa@gmail.com], [beguile])
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
PKG_CHECK_MODULES([CHECK], [check])

# Beguile modules
MODULE_PACKAGE=package.h
MODULE_UTIL=util.h
MODULE_CORE=core.h
MODULE_LANG_EN=lang_en.h
MODULE_SIGNALS=signals.h
MODULE_STYLE=style.h

MODULES="$MODULES header.h"
MODULES="$MODULES $MODULE_PACKAGE"
MODULES="$MODULES $MODULE_UTIL"
MODULES="$MODULES $MODULE_STYLE"
MODULES="$MODULES $MODULE_CORE"
MODULES="$MODULES $MODULE_LANG_EN"
MODULES="$MODULES $MODULE_SIGNALS"
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
