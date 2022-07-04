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
AM_M4FLAGS =
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

LDADD += $(CODE_COVERAGE_LIBS)

CODE_COVERAGE_IGNORE_PATTERN =
CODE_COVERAGE_IGNORE_PATTERN += /usr/include/*
CODE_COVERAGE_IGNORE_PATTERN += /usr/include/*/*

clean-local: code-coverage-clean sources-clean tests-clean
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

TOTAL_M4FLAGS =
TOTAL_M4FLAGS += $(AM_M4FLAGS)
TOTAL_M4FLAGS += $(M4FLAGS)
TOTAL_M4FLAGS += $(XM4FLAGS)

%.h: %.h.m4 common-macros.m4
	@$(MKDIR_P) $(@D)
	$(call v,M4)$(M4) $(TOTAL_M4FLAGS) $(<) > $(@)

@GNU@define uinttype_rule
@GNU@$1_keyed_radix_sort.c: uinttype_keyed_radix_sort.c.m4 common-macros.m4 GNUmakefile;
@GNU@	@$(MKDIR_P) $$(@D)
@GNU@	$$(call v,M4)$(M4) $(TOTAL_M4FLAGS) -DTYPE=$1 $$(<) > $$(@)
@GNU@endef

@GNU@define inttype_rule
@GNU@$1_keyed_radix_sort.c: inttype_keyed_radix_sort.c.m4 common-macros.m4 GNUmakefile;
@GNU@	@$(MKDIR_P) $$(@D)
@GNU@	$$(call v,M4)$(M4) $(TOTAL_M4FLAGS) -DTYPE=$1 $$(<) > $$(@)
@GNU@endef

EXTRA_DIST += uinttype_keyed_radix_sort.c.m4
EXTRA_DIST += inttype_keyed_radix_sort.c.m4

$(call uinttype_rule,uchar)
$(call uinttype_rule,usint)
$(call uinttype_rule,uint)
$(call uinttype_rule,ulint)
$(call uinttype_rule,ullint)
$(call uinttype_rule,uint8)
$(call uinttype_rule,uint16)
$(call uinttype_rule,uint32)
$(call uinttype_rule,uint64)
$(call uinttype_rule,uint128)
$(call uinttype_rule,uintmax)
$(call uinttype_rule,uintptr)
$(call uinttype_rule,size)

$(call inttype_rule,schar)
$(call inttype_rule,sint)
$(call inttype_rule,int)
$(call inttype_rule,lint)
$(call inttype_rule,llint)
$(call inttype_rule,int8)
$(call inttype_rule,int16)
$(call inttype_rule,int32)
$(call inttype_rule,int64)
$(call inttype_rule,int128)
$(call inttype_rule,intmax)
$(call inttype_rule,intptr)
$(call inttype_rule,ssize)

sources-clean:
	-rm -f *_keyed_radix_sort.c

#--------------------------------------------------------------------------

UINTTYPES = uchar,usint,uint,ulint,ullint,uint8,uint16,uint32,uint64,uint128,uintmax,uintptr,size
INTTYPES = schar,sint,int,lint,llint,int8,int16,int32,int64,int128,intmax,intptr,ssize

AM_M4FLAGS += -DUINTTYPES=$(UINTTYPES)
AM_M4FLAGS += -DINTTYPES=$(INTTYPES)

nodist_include_HEADERS =
nodist_include_HEADERS += integer-radix-sort.h

integer-radix-sort.h: GNUmakefile

CLEANFILES += integer-radix-sort.h
EXTRA_DIST += integer-radix-sort.h.m4

lib_LTLIBRARIES += libinteger-radix-sort.la
nodist_libinteger_radix_sort_la_SOURCES =
nodist_libinteger_radix_sort_la_SOURCES += uchar_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += usint_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += uint_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += ulint_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += ullint_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += uint8_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += uint16_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += uint32_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += uint64_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += uint128_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += uintmax_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += uintptr_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += size_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += schar_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += sint_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += int_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += lint_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += llint_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += int8_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += int16_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += int32_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += int64_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += int128_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += intmax_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += intptr_keyed_radix_sort.c
nodist_libinteger_radix_sort_la_SOURCES += ssize_keyed_radix_sort.c

#--------------------------------------------------------------------------

TESTS =
TESTS += tests/test-UINTTYPE_RADIX_SORT
TESTS += tests/test-INTTYPE_RADIX_SORT
TESTS += tests/test-stability

EXTRA_PROGRAMS += tests/test-UINTTYPE_RADIX_SORT
CLEANFILES += tests/test-UINTTYPE_RADIX_SORT
tests_test_UINTTYPE_RADIX_SORT_SOURCES =
tests_test_UINTTYPE_RADIX_SORT_SOURCES += tests/test-UINTTYPE_RADIX_SORT.c
tests_test_UINTTYPE_RADIX_SORT_SOURCES += integer-radix-sort.h

EXTRA_PROGRAMS += tests/test-INTTYPE_RADIX_SORT
CLEANFILES += tests/test-INTTYPE_RADIX_SORT
tests_test_INTTYPE_RADIX_SORT_SOURCES =
tests_test_INTTYPE_RADIX_SORT_SOURCES += tests/test-INTTYPE_RADIX_SORT.c
tests_test_INTTYPE_RADIX_SORT_SOURCES += integer-radix-sort.h

EXTRA_PROGRAMS += tests/test-stability
CLEANFILES += tests/test-stability
tests_test_stability_SOURCES =
tests_test_stability_SOURCES += tests/test-stability.c
tests_test_stability_SOURCES += integer-radix-sort.h

tests-clean:
	-rm -f tests/*.$(OBJEXT)
	-rm -f tests/*.sh

#--------------------------------------------------------------------------

nodist_pkgconfig_DATA += integer-radix-sort.pc

#--------------------------------------------------------------------------
# local variables:
# coding: utf-8
# end:
