// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <algorithm>
#include <format>
#include <limits>

#include "binomial.hh"
#include "bezier.hh"


Bezier::Bezier(std::span<Point> control_points):
  cp_bounding_box(2),
  bounding_box(2)
{
  validate_order();
  p.assign(control_points.begin(), control_points.end());
  flush_cached_data();
}

Bezier::Bezier(std::initializer_list<Point> control_points):
  p(control_points),
  cp_bounding_box(2),
  bounding_box(2)
{
  validate_order();
  flush_cached_data();
}

Bezier::Bezier(const Bezier& b):
  p(b.p),
  cp_bounding_box(2),
  bounding_box(2)
{
  flush_cached_data();
}

bool Bezier::operator==(const Bezier& other) const
{
  return other.p == p;
}

Bezier& Bezier::operator=(const Bezier& other)
{
  if (other.p != p)
  {
    p = other.p;
    flush_cached_data();
  }
  return *this;
}

int Bezier::order() const
{
  return p.size() - 1;
}

void Bezier::validate_order()
{
  if (order() < 2)
  {
    throw std::runtime_error(std::format("Bezier curve order ({}) must 2 or higher", order()));
  }
}

std::span<const Point> Bezier::get() const
{
  return std::span(p.begin(), p.size());
}

const Point& Bezier::get(std::size_t idx) const
{
  return p[idx];
}

void Bezier::set(std::size_t idx, const Point& point)
{
  if (point != p[idx])
  {
    p[idx] = point;
    flush_cached_data();
  };
}

const double Bezier::get(std::size_t idx, unsigned dimension) const
{
  return p[idx][dimension];
}

void Bezier::set(std::size_t idx, unsigned dimension, double value)
{
  if (value != p[idx][dimension])
  {
    p[idx][dimension] = value;
    flush_cached_data();
  }
}


void Bezier::flush_cached_data()
{
  cp_bounding_box.reset();
  bounding_box.reset();
  cp_convex_hull = nullptr;
}

Polynomial Bezier::compute_polynomial(unsigned dimension)
{
  if (dimension >= p[0].dimensionality())
  {
    throw std::runtime_error(std::format("Can't get poly for dimension {} of Bezier with {} dimensions", dimension, p[0].dimensionality()));
  }
  std::vector<double> coefficients;
  coefficients.assign(order()+1, 0.0);
  for (int i = 0; i <= order(); i++)
  {
    double bci = binomial_coefficient(order(), i);
    for (int j = 0; j <= i; j++)
    {
      double bcj = binomial_coefficient<double>(i, j);
      double c1 = p[j][dimension];
      double c = bci * bcj * c1;
      if ((i ^ j) & 1)
      {
	c = -c;
      }
      //std::cout << std::format("i={} j={} bci={} bcj={} p[{}][{}]={}, c={}\n", i, j, bci, bcj, j, dimension, c1, c);
      coefficients[i] += c;
    }
  }
  Polynomial p(coefficients);
  return p;
}


Rect Bezier::get_control_point_bounding_box()
{
  if (cp_bounding_box.empty())
  {
    cp_bounding_box.add_points(p);
    //std::cout << "Bezier control point bounding box " << cp_bounding_box << "\n";
  }
  return cp_bounding_box;
}

Polygon Bezier::get_control_point_convex_hull()
{
  if (! cp_convex_hull)
  {
    Polygon cp(p);
    cp_convex_hull = std::make_unique<Polygon>(cp.convex_hull());
  }
  return *cp_convex_hull;
}

Rect Bezier::get_bounding_box()
{
  // https://floris.briolas.nl/floris/2009/10/bounding-box-of-cubic-bezier/
  // https://stackoverflow.com/questions/24809978/calculating-the-bounding-box-of-cubic-bezier-curve

  if (bounding_box.empty())
  {
    std::vector<Polynomial> polynomials;
    std::vector<Polynomial> derivatives;

    for (int dimension = 0; dimension < p[0].dimensionality(); dimension++)
    {
      Polynomial poly = compute_polynomial(dimension);
      //std::cout << std::format("polynomial[{}] = ", dimension) << poly << "\n";
      polynomials.push_back(poly);

      Polynomial d = poly.derivative();
      //std::cout << std::format("derivative[{}] = ", dimension) << d << "\n";
      derivatives.push_back(d);
    }

    bounding_box = Rect(2, { p[0], p[order()] });

    for (int dimension = 0; dimension < p[0].dimensionality(); dimension++)
    {
      std::vector<double> roots = derivatives[dimension].real_roots(0.0, 1.0);
      for (auto t: roots)
      {
	Point rp {polynomials[X](t), polynomials[Y](t) };
	//std::cout << std::format("dim {} root at t = {}, point", dimension, t) << rp << "\n";
	bounding_box.add_point(rp);
      }
    }
  }

  return bounding_box;
}

std::ostream& operator<<(std::ostream& os, const Bezier& bezier)
{
  auto it = bezier.p.cbegin();
  os << "Bezier(" << *it++;
  while (it != bezier.p.cend())
  {
    os << ", " << *it++;
  }
  os << ")";
  return os;
}
