// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef BINOMIAL_HH
#define BINOMIAL_HH

// Calcuates the number of combinations of m things taken n at a time.
// If n is less than laf of m, then the function calculates the
// combinations of m things taken m-n at a time, which is the exact
// equvalent of m things taken n at a time.
// Reference:
//    ACM Algorithm 160
//    Combinatorial of M Things Taken N at a Time
//    M.L. Wolfson and H.V. Wright
//    United States Steel Corp., Monroevill, PA
//    Communications of the ACM, Vol. 6 No. 4, p. 161
//    https://doi.org/10.1145/366349.366432

#include <concepts>

template<typename T>
requires std::integral<T> || std::floating_point<T>
T binomial_coefficient(T m, T n)
{
  T p = m - n;
  if (n < p)
  {
    p = n;
    n = m - p;
  }
  if (p == 0)
  {
    return 1;
  }
  T r = n + 1;
  for (int i = 2; i <= p; i++)
  {
    r *= (n + i);
    r /= i;
  }
  return r;
}

#endif // BINOMIAL_HH
