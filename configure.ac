#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Beguile], [0.1.0], [superruzafa@gmail.com], [beguile])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/package.h.in])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# Beguile modules
MODULE_PACKAGE=package.h

MODULES="$MODULES header.h"
MODULES="$MODULES $MODULE_PACKAGE"
MODULES="$MODULES footer.h"
AC_SUBST([MODULES])

AC_CONFIG_FILES([Makefile src/Makefile src/package.h tests/Makefile])
AC_OUTPUT
