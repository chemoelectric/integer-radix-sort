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

#ifndef INTEGER_RADIX_SORT_H_HEADER_GUARD__
#define INTEGER_RADIX_SORT_H_HEADER_GUARD__

#include <stdint.h>
#include <string.h>

#if defined __GNUC__
#define INTEGER_RADIX_SORT__MEMSET __builtin_memset
#else
#define INTEGER_RADIX_SORT__MEMSET memset
#endif

#define INTEGER_RADIX_SORT__BIN_SIZES_TO_INDICES(PFX, BIN_INDICES)  \
  do                                                                \
    {                                                               \
      size_t PFX##accum = 0;                                        \
      for (size_t PFX##i = 0; PFX##i != 256; PFX##i += 1)           \
        {                                                           \
          size_t PFX##elem = (BIN_INDICES)[PFX##i];                 \
          if (PFX##elem != 0)                                       \
            {                                                       \
              (BIN_INDICES)[PFX##i] = PFX##accum;                   \
              PFX##accum += PFX##elem;                              \
            }                                                       \
        }                                                           \
    }                                                               \
  while (0)

#define INTEGER_RADIX_SORT__COUNT_ENTRIES(PFX, KEY_T, GET_KEY, ARR, \
                                          NMEMB, SIZE, BIN_INDICES, \
                                          ALL_EXPENDED, SHIFT)      \
  do                                                                \
    {                                                               \
      ALL_EXPENDED = 1;                                             \
      INTEGER_RADIX_SORT__MEMSET ((BIN_INDICES),                    \
                                  256 * sizeof (size_t), 0);        \
      for (size_t PFX##i = 0; PFX##i != (NMEMB); PFX##i += 1)       \
        {                                                           \
          KEY_T PFX##key = GET_KEY ((ARR) + PFX##i * (SIZE));       \
          unsigned int PFX##key_shifted = (PFX##key >> (SHIFT));    \
          unsigned int PFX##digit = (PFX##key_shifted & 255U);      \
          size_t PFX##count = (BIN_INDICES)[PFX##digit];            \
          (BIN_INDICES)[PFX##digit] = PFX##count + 1;               \
          ALL_EXPENDED =                                            \
            ((ALL_EXPENDED) & (PFX##key_shifted == 0));             \
        }                                                           \
    }                                                               \
  while (0)


/* fn {a  : vt@ype} */
/*    {tk : tkind} */
/* sort_by_digit */
/*           {n            : int} */
/*           {shift        : nat} */
/*           (arr1         : &RD(array (a, n)), */
/*            arr2         : &array (a, n) >> _, */
/*            n            : size_t n, */
/*            all_expended : &bool? >> bool, */
/*            shift        : int shift) */
/*     :<!wrt> void = */
/*   let */
/*     var bin_indices : array (size_t, 256) */
/*   in */
/*     count_entries<a><tk> (arr1, n, bin_indices, all_expended, shift); */
/*     if all_expended then */
/*       () */
/*     else */
/*       let */
/*         fun */
/*         rearrange {i : int | i <= n} */
/*                   .<n - i>. */
/*                   (arr1        : &RD(array (a, n)), */
/*                    arr2        : &array (a, n) >> _, */
/*                    bin_indices : &array (size_t, 256) >> _, */
/*                    i           : size_t i) */
/*             :<!wrt> void = */
/*           if i <> n then */
/*             let */
/*               prval () = lemma_g1uint_param i */
/*               val key = g0uint_radix_sort$key<a><tk> (arr1, i) */
/*               val key_shifted = key >> shift */
/*               val digit = ($UN.cast{uint} key_shifted) land 255U */
/*               val [digit : int] digit = g1ofg0 digit */
/*               extern praxi set_range : */
/*                 () -<prf> [0 <= digit; digit <= 255] void */
/*               prval () = set_range () */
/*               val [j : int] j = g1ofg0 bin_indices[digit] */

/*               (* One might wish to get rid of this assertion somehow, */
/*                  to eliminate the branch, should it prove a */
/*                  problem. *) */
/*               val () = $effmask_exn assertloc (j < n) */

/*               val p_dst = ptr_add<a> (addr@ arr2, j) */
/*               and p_src = ptr_add<a> (addr@ arr1, i) */
/*               val () = copy_memory (p_dst, p_src, sizeof<a>) */
/*               val () = bin_indices[digit] := succ (g0ofg1 j) */
/*             in */
/*               rearrange (arr1, arr2, bin_indices, succ i) */
/*             end */

/*         prval () = lemma_array_param arr1 */
/*       in */
/*         bin_sizes_to_indices<> bin_indices; */
/*         rearrange (arr1, arr2, bin_indices, i2sz 0) */
/*       end */
/*   end */


#endif INTEGER_RADIX_SORT_H_HEADER_GUARD__
