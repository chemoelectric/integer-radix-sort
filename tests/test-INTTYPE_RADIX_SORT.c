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

static int
intcmp (const void *px, const void *py)
{
  const int x = *((const int *) px);
  const int y = *((const int *) py);
  return ((x < y) ? -1 : ((x > y) ? 1 : 0));
}

static void
test_random_arrays (void)
{
  printf ("Random int in -1000..1000\n");
  for (size_t sz = 0; sz <= MAX_SZ; sz = MAX (1, 10 * sz))
    {
      int *p1 = malloc (sz * sizeof (int));
      int *p2 = malloc (sz * sizeof (int));
      int *p3 = malloc (sz * sizeof (int));

      for (size_t i = 0; i < sz; i += 1)
        p1[i] = random_int (-1000, 1000);

      for (size_t i = 0; i < sz; i += 1)
        p2[i] = p1[i];
      clock_t tq1 = clock ();
      qsort (p2, sz, sizeof (int), intcmp);
      clock_t tq2 = clock ();
      long double tq = ((long double) (tq2 - tq1)) / CLOCKS_PER_SEC;

      for (size_t i = 0; i < sz; i += 1)
        p3[i] = p1[i];
      clock_t tr1 = clock ();
      INTTYPE_RADIX_SORT (int, unsigned int, p3, sz);
      clock_t tr2 = clock ();
      long double tr = ((long double) (tr2 - tr1)) / CLOCKS_PER_SEC;

      for (size_t i = 0; i < sz; i += 1)
        CHECK (p2[i] == p3[i]);

      printf ("  size:%9zu   qsort: %Lf   radix: %Lf\n", sz, tq, tr);

      free (p1);
      free (p2);
      free (p3);
    }
}

/*------------------------------------------------------------------*/

int
main (int argc, char *argv[])
{
  test_random_arrays ();
  return 0;
}

/*------------------------------------------------------------------*/
