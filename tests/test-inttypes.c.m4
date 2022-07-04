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

#include <stdio.h>
#include <time.h>
#include <integer-radix-sort.h>

/*------------------------------------------------------------------*/
/* A simple linear congruential generator.                          */

/* The multiplier LCG_A comes from Steele, Guy; Vigna, Sebastiano (28
   September 2021). "Computationally easy, spectrally good multipliers
   for congruential pseudorandom number generators".
   arXiv:2001.05304v3 [cs.DS] */
#define LCG_A UINT64_C(0xf1357aea2e62a9c5)

/* LCG_C must be odd. */
#define LCG_C UINT64_C(0xbaceba11beefbead)

uint64_t seed = 0;

static double
random_double (void)
{
  /* IEEE "binary64" or "double" has 52 bits of precision. We will
     take the high 48 bits of the seed and divide it by 2**48, to get
     a number 0.0 <= randnum < 1.0 */
  const double high_48_bits = (double) (seed >> 16);
  const double divisor = (double) (UINT64_C(1) << 48);
  const double randnum = high_48_bits / divisor;

  /* The following operation is modulo 2**64, by virtue of standard C
     behavior for uint64_t. */
  seed = (LCG_A * seed) + LCG_C;

  return randnum;
}

static int
random_int (int m, int n)
{
  return m + (int) (random_double () * (n - m + 1));
}

/*------------------------------------------------------------------*/

#define MAX_SZ 10000000

#define MAX(x, y) (((x) < (y)) ? (y) : (x))

#define CHECK(expr)                             \
  if (expr)                                     \
    {}                                          \
  else                                          \
    check_failed (__FILE__, __LINE__)

static void
check_failed (const char *file, unsigned int line)
{
  fprintf (stderr, "CHECK failed at %s:%u\n", file, line);
  exit (1);
}

m4_foreachq(`TYPE',`INTTYPES',
`m4_if(TYPE,`int128',`#if defined __SIZEOF_INT128__
')dnl
static int
TYPE`'_cmp (const void *px, const void *py)
{
  const m4_map_typename(TYPE) x =
    *((const m4_map_typename(TYPE) *) px);
  const m4_map_typename(TYPE) y =
    *((const m4_map_typename(TYPE) *) py);
  return ((x < y) ? -1 : ((x > y) ? 1 : 0));
}
m4_if(TYPE,`int128',`#endif
')dnl

')

m4_foreachq(`TYPE',`INTTYPES',
`m4_if(TYPE,`int128',`#if defined __SIZEOF_INT128__
')dnl
static void
test_`'TYPE`'_random_arrays (void)
{
  for (size_t sz = 0; sz <= MAX_SZ; sz = MAX (1, 10 * sz))
    {
      m4_map_typename(TYPE) *p1 = malloc (sz * sizeof (m4_map_typename(TYPE)));
      m4_map_typename(TYPE) *p2 = malloc (sz * sizeof (m4_map_typename(TYPE)));
      m4_map_typename(TYPE) *p3 = malloc (sz * sizeof (m4_map_typename(TYPE)));

      for (size_t i = 0; i < sz; i += 1)
        p1[i] = random_int (1, 1000);

      for (size_t i = 0; i < sz; i += 1)
        p2[i] = p1[i];
      qsort (p2, sz, sizeof (m4_map_typename(TYPE)), TYPE`'_cmp);

      for (size_t i = 0; i < sz; i += 1)
        p3[i] = p1[i];
      TYPE`'_keyed_radix_sort (p3, sz, sizeof (m4_map_typename(TYPE)), NULL);

      for (size_t i = 0; i < sz; i += 1)
        CHECK (p2[i] == p3[i]);

      free (p1);
      free (p2);
      free (p3);
    }
}
m4_if(TYPE,`int128',`#endif
')dnl

')

/*------------------------------------------------------------------*/

int
main (int argc, char *argv[])
{
m4_foreachq(`TYPE',`INTTYPES',
`m4_if(TYPE,`int128',`#if defined __SIZEOF_INT128__
')dnl
  test_`'TYPE`'_random_arrays ();
m4_if(TYPE,`int128',`#endif
')dnl
')
  return 0;
}

/*------------------------------------------------------------------*/

/* local variables: */
/* mode: c */
/* end: */
