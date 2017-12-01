#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libclastic], [1.0], [phuong.do@igloosec.com])
AC_CONFIG_SRCDIR([src/clastic.c])
AM_INIT_AUTOMAKE([subdir-objects])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# Enable debug
AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug],
            [Enable verbose debug output to be compiled @<:@no@:>@])],
    [debug="$enableval"],
    [debug="no"])
AM_CONDITIONAL([DEBUG], [test x$debug = xyes])

AC_CONFIG_FILES([Makefile
                    include/Makefile
                    src/Makefile
                ])
AC_OUTPUT
