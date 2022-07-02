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
#include <stdint.h>
#include <string.h>
#include <integer-radix-sort.h>

/*------------------------------------------------------------------*/

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

static uint64_t
get_key (void *p)
{
  const uint8_t *s = *(const uint8_t **) p;
  const uint64_t c3 = s[0];
  const uint64_t c2 = s[1];
  const uint64_t c1 = s[2];
  const uint64_t c0 = s[3];
  return (c3 << 24) | (c2 << 16) | (c1 << 8) | c0;
}

#define GET_KEY(KEY_T, PTR) get_key (PTR)

static void
test_stability (void)
{
  const char *data[19] =
    { "forewarned", "overshoot", "pansy", "forewarn",
      "forecastle", "pans", "pansophies", "overbear",
      "forest", "overt", "foreclose", "pansexuality",
      "overly", "overopinionated", "pansexual",
      "pansophy", "forelorn", "overbearing", "fore" };

  const char *expected[19] =
    { "forewarned", "forewarn", "forecastle", "forest",
      "foreclose", "forelorn", "fore", "overshoot",
      "overbear", "overt", "overly", "overopinionated",
      "overbearing", "pansy", "pans", "pansophies",
      "pansexuality", "pansexual", "pansophy" };

  UINTTYPE_KEYED_RADIX_SORT (uint64_t, data, 19,
                             sizeof (const char *), GET_KEY);

  for (size_t i = 0; i != 19; i += 1)
    printf("\"%s\"\n", data[i]);
  for (size_t i = 0; i != 19; i += 1)
    CHECK (strcmp (data[i], expected[i]) == 0);
}

/*------------------------------------------------------------------*/

int
main (int argc, char *argv[])
{
  test_stability ();
  return 0;
}

/*------------------------------------------------------------------*/
