/*
  Copyright © 2022 Barry Schwartz

  This program is free software: you can redistribute it and/or
  modify it under the terms of the GNU General Public License, as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received copies of the GNU General Public License
  along with this program. If not, see
  <https://www.gnu.org/licenses/>.
*/
include(`common-macros.m4')dnl

#include <integer-radix-sort.h>

#define GET_KEY__(KEY_T, PTR) \
  ((get_key != NULL) ? (get_key (PTR)) : (*(const KEY_T *)(PTR)))

m4_if(TYPE,`int128',`#if defined __SIZEOF_INT128__
')dnl
void
TYPE`'_keyed_radix_sort (void *base, size_t nmemb, size_t size,
                       m4_map_typename(TYPE) (*get_key) (void *))
{
  INTTYPE_KEYED_RADIX_SORT (m4_map_typename(TYPE), m4_map_typename(m4_signed_to_unsigned(TYPE)),
                            base, nmemb, size, GET_KEY__);
}
m4_if(TYPE,`int128',`#endif
')dnl

/* local variables: */
/* mode: c */
/* end: */
