#
# Copyright © 2022 Barry Schwartz
#
# This program is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License, as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received copies of the GNU General Public License
# along with this program. If not, see
# <https://www.gnu.org/licenses/>.
#

.DELETE_ON_ERROR:

ACLOCAL_AMFLAGS = -I m4 --install
AUTOMAKE_OPTIONS =
AUTOMAKE_OPTIONS += foreign
AUTOMAKE_OPTIONS += subdir-objects

include $(top_srcdir)/aminclude_static.am
@GNU@ include $(top_srcdir)/silent-rules.mk

EXTRA_DIST =
MOSTLYCLEANFILES =
CLEANFILES =
DISTCLEANFILES =
BUILT_SOURCES =
AM_CPPFLAGS =
AM_CFLAGS =
AM_LDFLAGS =
LDADD =
bin_PROGRAMS =
lib_LTLIBRARIES =
EXTRA_PROGRAMS =
nobase_nodist_pkginclude_HEADERS =
nodist_pkgconfig_DATA =

EXTRA_DIST += $(srcdir)/silent-rules.mk
EXTRA_DIST += COPYING
EXTRA_DIST += INSTALL
EXTRA_DIST += README
EXTRA_DIST += AUTHORS

DISTCLEANFILES += Makefile
DISTCLEANFILES += GNUmakefile

AM_CPPFLAGS += -I$(builddir)
AM_CPPFLAGS += -I$(srcdir)
AM_CPPFLAGS += -I$(PATSHOME)
AM_CPPFLAGS += -I$(PATSHOME)/ccomp/runtime/

LDADD += $(CODE_COVERAGE_LIBS)

CODE_COVERAGE_IGNORE_PATTERN =
CODE_COVERAGE_IGNORE_PATTERN += /usr/include/*
CODE_COVERAGE_IGNORE_PATTERN += /usr/include/*/*
CODE_COVERAGE_IGNORE_PATTERN += $(PATSHOME)/ccomp/runtime/*
CODE_COVERAGE_IGNORE_PATTERN += $(PATSHOME)/prelude/CATS/*

clean-local: code-coverage-clean tests-clean
distclean-local: code-coverage-dist-clean

#---------------------------------------------------------------------
#
# Some GNU Make aids you might want to use.
#

comma := ,
empty :=
space := $(empty) $(empty)

# Escape things for sed expressions, etc.
escape = $(subst $$,\$$,$(subst ^,\^,$(subst ],\],$(subst [,\[,$(subst .,\.,$(subst \,\\,$(1)))))))

#--------------------------------------------------------------------------

include_HEADERS =
include_HEADERS += integer-radix-sort.h

#--------------------------------------------------------------------------

TESTS =
TESTS += tests/test-UINTTYPE_RADIX_SORT
TESTS += tests/test-INTTYPE_RADIX_SORT
TESTS += tests/test-stability

EXTRA_PROGRAMS += tests/test-UINTTYPE_RADIX_SORT
CLEANFILES += tests/test-UINTTYPE_RADIX_SORT
tests_test_UINTTYPE_RADIX_SORT_SOURCES =
tests_test_UINTTYPE_RADIX_SORT_SOURCES += tests/test-UINTTYPE_RADIX_SORT.c

EXTRA_PROGRAMS += tests/test-INTTYPE_RADIX_SORT
CLEANFILES += tests/test-INTTYPE_RADIX_SORT
tests_test_INTTYPE_RADIX_SORT_SOURCES =
tests_test_INTTYPE_RADIX_SORT_SOURCES += tests/test-INTTYPE_RADIX_SORT.c

EXTRA_PROGRAMS += tests/test-stability
CLEANFILES += tests/test-stability
tests_test_stability_SOURCES =
tests_test_stability_SOURCES += tests/test-stability.c

tests-clean:
	-rm -f tests/*.$(OBJEXT)
	-rm -f tests/*.sh

#--------------------------------------------------------------------------

nodist_pkgconfig_DATA += integer-radix-sort.pc

#--------------------------------------------------------------------------
# local variables:
# coding: utf-8
# end:
