// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef POLYNOMIAL_HH
#define POLYNOMIAL_HH

#include <complex>
#include <concepts>
#include <exception>
#include <format>
#include <initializer_list>
#include <iostream>
#include <ranges>
#include <span>
#include <vector>

class Polynomial
{
public:
  Polynomial(std::span<double> coefficients);
  Polynomial(std::initializer_list<double> coefficients);

  double operator() (double x) const;

  const double& operator[](std::size_t idx) const;

  inline size_t order() const
  {
    return cv.size() - 1;
  }

  Polynomial derivative() const;

  std::vector<std::complex<double>> roots() const;

  std::vector<double> real_roots(double min = -std::numeric_limits<double>::infinity(),
				 double max =  std::numeric_limits<double>::infinity()) const;

  friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);

private:
  std::vector<double> cv;  // coefficient vector

  void drop_high_zero_terms();
};

#endif // POLYNOMIAL
