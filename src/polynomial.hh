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

template<typename T = double>
requires std::floating_point<T>
class Polynomial
{
public:
  Polynomial(std::vector<T> coefficients):
    cv(coefficients)
  {
    drop_high_zero_terms();
  }

  Polynomial(std::initializer_list<T> coefficients):
    cv(std::ranges::crbegin(coefficients), std::ranges::crend(coefficients))
  {
    drop_high_zero_terms();
  }

  const T& operator() (T x) const
  {
    // Evaluate polynomial using horner's method
    auto it = cv.begin();
    T r = *(it++);
    while (it != cv.crend())
    {
      r *= x;
      r += *(it++);
    }
    return r;
  }

  const T& operator[](std::size_t idx) const
  {
    return cv[idx];
  }

  inline size_t order() const
  {
    return cv.size() - 1;
  }

  Polynomial derivative() const
  {
    if (order() < 1)
    {
      throw std::runtime_error(std::format("can't take derivative of polynomial of order {}",
					   order()));
    }

    std::vector<T> dc;  // one fewer element than this
    for (int i = 1; i < cv.size(); i++)
    {
      dc.push_back(i * cv[i]);
    }

    return Polynomial(dc);
  }

  std::vector<std::complex<T>> roots() const
  {
    std::vector<std::complex<T>> crv;
    switch (order())
    {
    case 1:
      crv.push_back(std::complex<T>(-cv[1]/cv[0], 0));
      break;

    case 2:
      {
        auto discriminant = std::complex<T>(cv[1] * cv[1] - 4 * cv[2] * cv[0], 0);
        auto sqrt_of_d = std::sqrt(discriminant);
        crv.push_back((-cv[1] + sqrt_of_d) / (2 * cv[2]));
        crv.push_back((-cv[1] - sqrt_of_d) / (2 * cv[2]));
      }
      break;

    default:
      throw std::runtime_error(std::format("requested roots of polynomial of order {}",
					   order()));
    }

    return crv;
  }

  std::vector<T> real_roots() const
  {
    std::vector<T> rrv;
    for (auto cr: roots())
    {
      if (cr.imag() == 0.0)
	rrv.push_back(cr.real());
    }
    return rrv;
  }

  // This declaration causes "redeclared without dllimport attribute" when cross-compiling using
  // g++ for a Windows target. Sadly, adding the __declspec(dllimport) doesn't solve it.
  friend std::ostream& operator<<(std::ostream& os, const Polynomial& p)
  {
    auto it = p.cv.crbegin();
    os << "Polynomial(" << *it++;
    while (it != p.cv.crend())
    {
      os << ", " << *it++;
    }
    os << ")";
    return os;
  }

private:
  std::vector<T> cv;  // coefficient vector

  void drop_high_zero_terms()
  {
    while((cv.size() != 0) && (cv.back() == 0))
    {
      cv.pop_back();
    }
    if (cv.size() == 0)
    {
      throw std::runtime_error("polynomial has non non-zero terms");
    }
  }
};

void polynomial_test(void);

#endif // POLYNOMIAL
