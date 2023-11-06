// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include "polynomial.hh"

void polynomial_test(void)
{
  Polynomial<float> pf1({3.2, 5.6, 7.44});  // constant term last, 3.2 x^2 + 5.6 x + 7.44
  std::cout << "pf1: " << pf1 << "\n";

  Polynomial<double> pd1 {3.2, 5.6, 7.44};  // constant term last
  std::cout << "pd1: " << pd1 << "\n";

  Polynomial<double> pd2(std::vector<double> {7.44, 5.6, 3.2});  // constant term first
  std::cout << "pd2: " << pd2 << "\n";

  Polynomial<double> pd3 {1.0/3, -0.125, -0.125, 3.9};  // constant term last
  std::cout << "pd3: " << pd3 << "\n";

  auto pd3p = pd3.derivative();
  std::cout << "pd3p: " << pd3p << "\n";

  auto crv = pd3p.roots();
  std::cout << std::format("{} complex roots\n", crv.size());
  for (auto cr: crv)
  {
    std::cout << cr << "\n";
  }

  auto rrv = pd3p.real_roots();
  std::cout << std::format("{} real roots\n", rrv.size());
  for (auto rr: rrv)
  {
    std::cout << rr << "\n";
  }
}
