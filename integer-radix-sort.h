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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#if defined __GNUC__
#define INTEGER_RADIX_SORT__MEMSET __builtin_memset
#define INTEGER_RADIX_SORT__MEMCPY __builtin_memcpy
#else
#define INTEGER_RADIX_SORT__MEMSET memset
#define INTEGER_RADIX_SORT__MEMCPY memcpy
#endif

#define INTEGER_RADIX_SORT__SIZE_THRESHOLD 2048

#define INTEGER_RADIX_SORT__DEREFERENCE(KEY_T, PTR) \
  (*(const KEY_T *)(PTR))

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
      for (size_t PFX##i = 0; PFX##i != (NMEMB); PFX##i += 1)       \
        {                                                           \
          KEY_T PFX##key =                                          \
            GET_KEY                                                 \
            (KEY_T, (void *) ((char *) (ARR)) + PFX##i * (SIZE));   \
          unsigned int PFX##key_shifted = (PFX##key >> (SHIFT));    \
          unsigned int PFX##digit = (PFX##key_shifted & 255U);      \
          size_t PFX##count = (BIN_INDICES)[PFX##digit];            \
          (BIN_INDICES)[PFX##digit] = PFX##count + 1;               \
          ALL_EXPENDED =                                            \
            ((ALL_EXPENDED) & (PFX##key_shifted == 0));             \
        }                                                           \
    }                                                               \
  while (0)

#define INTEGER_RADIX_SORT__SORT_BY_DIGIT(PFX, KEY_T, GET_KEY,      \
                                          ARR1, ARR2, NMEMB, SIZE,  \
                                          ALL_EXPENDED, SHIFT)      \
  do                                                                \
    {                                                               \
      size_t PFX##bin_indices[256];                                 \
      INTEGER_RADIX_SORT__MEMSET (PFX##bin_indices, 0,              \
                                  256 * sizeof (size_t));           \
      INTEGER_RADIX_SORT__COUNT_ENTRIES (PFX, KEY_T, GET_KEY,       \
                                         (ARR1), (NMEMB), (SIZE),   \
                                         PFX##bin_indices,          \
                                         ALL_EXPENDED, (SHIFT));    \
      if (!(ALL_EXPENDED))                                          \
        {                                                           \
          INTEGER_RADIX_SORT__BIN_SIZES_TO_INDICES                  \
            (PFX, PFX##bin_indices);                                \
          for (size_t PFX##i = 0; PFX##i != (NMEMB); PFX##i += 1)   \
            {                                                       \
              const void *PFX##p_src =                              \
                ((const char *) (ARR1)) + (PFX##i * (SIZE));        \
              KEY_T PFX##key =                                      \
                GET_KEY (KEY_T, (void *) PFX##p_src);               \
              unsigned int PFX##key_shifted =                       \
                (PFX##key >> (SHIFT));                              \
              unsigned int PFX##digit = (PFX##key_shifted & 255U);  \
              size_t PFX##j = PFX##bin_indices[PFX##digit];         \
              void *PFX##p_dst =                                    \
                ((char *) (ARR2)) + (PFX##j * (SIZE));              \
              INTEGER_RADIX_SORT__MEMCPY (PFX##p_dst, PFX##p_src,   \
                                          SIZE);                    \
              PFX##bin_indices[PFX##digit] = PFX##j + 1;            \
            }                                                       \
        }                                                           \
    }                                                               \
  while (0)

#define INTEGER_RADIX_SORT__INTEGER_RADIX_SORT(PFX, KEY_T, GET_KEY, \
                                               ARR, NMEMB, SIZE)    \
  do                                                                \
    {                                                               \
      size_t PFX##total_size = (NMEMB) * (SIZE);                    \
      size_t PFX##use_stack =                                       \
        PFX##total_size <= (INTEGER_RADIX_SORT__SIZE_THRESHOLD);    \
      size_t PFX##stack_space;                                      \
      if (PFX##use_stack)                                           \
        PFX##stack_space = PFX##total_size;                         \
      else                                                          \
        PFX##stack_space = 1;                                       \
      char PFX##stack[PFX##stack_space];                            \
      char *PFX##arr2;                                              \
      if (PFX##use_stack)                                           \
        PFX##arr2 = PFX##stack;                                     \
      else                                                          \
        {                                                           \
          PFX##arr2 = malloc (PFX##total_size);                     \
          if (PFX##arr2 == NULL)                                    \
            {                                                       \
              fprintf (stderr, "Memory exhausted");                 \
              exit (1);                                             \
            }                                                       \
        }                                                           \
                                                                    \
      int PFX##from1to2 = 1;                                        \
      int PFX##all_expended = 0;                                    \
      int PFX##idigit = 0;                                          \
      while (!PFX##all_expended && PFX##idigit != sizeof (KEY_T))   \
        {                                                           \
          if (PFX##from1to2)                                        \
            INTEGER_RADIX_SORT__SORT_BY_DIGIT(PFX, KEY_T, GET_KEY,  \
                                              (ARR), PFX##arr2,     \
                                              (NMEMB), (SIZE),      \
                                              PFX##all_expended,    \
                                              8 * PFX##idigit);     \
          else                                                      \
            INTEGER_RADIX_SORT__SORT_BY_DIGIT(PFX, KEY_T, GET_KEY,  \
                                              PFX##arr2, (ARR),     \
                                              (NMEMB), (SIZE),      \
                                              PFX##all_expended,    \
                                              8 * PFX##idigit);     \
          PFX##idigit += 1;                                         \
        }                                                           \
      if (!PFX##from1to2)                                           \
        INTEGER_RADIX_SORT__MEMCPY ((ARR), PFX##arr2,               \
                                    PFX##total_size);               \
                                                                    \
      if (!PFX##use_stack)                                          \
        free (PFX##arr2);                                           \
    }                                                               \
  while (0)

#define INTEGER_RADIX_SORT(KEY_T, ARR, NMEMB, SIZE, GET_KEY)        \
  INTEGER_RADIX_SORT__INTEGER_RADIX_SORT(_integer_radix_sort__,     \
                                         KEY_T, GET_KEY,            \
                                         (ARR), (NMEMB), (SIZE))

/* For example:

     UINTTYPE_RADIX_SORT (uintmax_t, array1, num_elements);

*/
#define UINTTYPE_RADIX_SORT(KEY_T, ARR, NMEMB)                  \
  INTEGER_RADIX_SORT (KEY_T, (ARR), (NMEMB), sizeof (KEY_T),    \
                      INTEGER_RADIX_SORT__DEREFERENCE)

#endif /* INTEGER_RADIX_SORT_H_HEADER_GUARD__ */
