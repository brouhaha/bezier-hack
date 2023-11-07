// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include "polynomial.hh"

Polynomial::Polynomial(std::span<double> coefficients)
{
  cv.assign(coefficients.begin(), coefficients.end());
  drop_high_zero_terms();
}

Polynomial::Polynomial(std::initializer_list<double> coefficients):
  cv(std::ranges::crbegin(coefficients), std::ranges::crend(coefficients))
{
  drop_high_zero_terms();
}

double Polynomial::operator() (double x) const
{
  // Evaluate polynomial using horner's method
  auto it = cv.crbegin();
  double r = *(it++);
  while (it != cv.crend())
  {
    r *= x;
    r += *(it++);
  }
  return r;
}

const double& Polynomial::operator[](std::size_t idx) const
{
  return cv[idx];
}

Polynomial Polynomial::derivative() const
{
  if (order() < 1)
  {
    throw std::runtime_error(std::format("can't take derivative of polynomial of order {}",
					 order()));
  }

  std::vector<double> dc;  // one fewer element than this
  for (int i = 1; i < cv.size(); i++)
  {
    double v = i * cv[i];
    dc.push_back(v);
  }

  return Polynomial(dc);
}

std::vector<std::complex<double>> Polynomial::roots() const
{
  std::vector<std::complex<double>> crv;
  switch (order())
  {
  case 1:
    crv.push_back(std::complex<double>(-cv[1]/cv[0], 0));
    break;

  case 2:
  {
    auto discriminant = std::complex<double>(cv[1] * cv[1] - 4 * cv[2] * cv[0], 0);
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

std::vector<double> Polynomial::real_roots(double min,
					   double max) const
{
  std::vector<double> rrv;
  for (auto cr: roots())
  {
    if ((cr.imag() == 0.0) && (cr.real() >= min) && (cr.real() <= max))
      rrv.push_back(cr.real());
  }
  return rrv;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p)
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

void Polynomial::drop_high_zero_terms()
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


#if 0
#include <iostream>
#include <format>

int main([[maybe_unused]] int argc,
	 [[maybe_unused]] char*argv[])
{
  Polynomial pf1({3.2, 5.6, 7.44});  // constant term last, 3.2 x^2 + 5.6 x + 7.44
  std::cout << "pf1: " << pf1 << "\n";

  Polynomial pd1 {3.2, 5.6, 7.44};  // constant term last
  std::cout << "pd1: " << pd1 << "\n";

  Polynomial pd2(std::vector<double> {7.44, 5.6, 3.2});  // constant term first
  std::cout << "pd2: " << pd2 << "\n";

  Polynomial pd3 {1.0/3, -0.125, -0.125, 3.9};  // constant term last
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

#endif
