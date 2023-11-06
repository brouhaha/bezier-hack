// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef POLYNOMIAL_HH
#define POLYNOMIAL_HH

#include <array>
#include <complex>
#include <concepts>
#include <exception>
#include <format>
#include <initializer_list>
#include <iostream>
#include <ranges>
#include <vector>

class Polynomial
{
public:
  Polynomial(std::vector<double> coefficients);
  Polynomial(std::initializer_list<double> coefficients);

  double operator() (double x) const;

  const double& operator[](std::size_t idx) const;

  inline size_t order() const
  {
    return cv.size() - 1;
  }

  Polynomial derivative() const;

  std::vector<std::complex<double>> roots() const;

  std::vector<double> real_roots() const;

  friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);

private:
  std::vector<double> cv;  // coefficient vector

  void drop_high_zero_terms();
};

#endif // POLYNOMIAL
