// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <algorithm>
#include <iostream>
#include <limits>

#include "bezier.hh"


Bezier::Bezier(std::span<Point> control_points):
  cp_bounding_box(2),
  bounding_box(2)
{
  validate_order();
  p.assign(control_points.begin(), control_points.end());
}

Bezier::Bezier(std::initializer_list<Point> control_points):
  p(control_points),
  cp_bounding_box(2),
  bounding_box(2)
{
  validate_order();
}

Bezier::Bezier(const Bezier& b):
  p(b.p),
  cp_bounding_box(2),
  bounding_box(2)
{
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
  poly.clear();
}

Polynomial Bezier::get_poly(unsigned dimension)
{
 // XXXXXX size of poly needs to be established somewhere
  if (dimension >= poly.size())
  {
    throw std::runtime_error(std::format("Can't get poly for dimension {} of Bezier with {} dimensions", dimension, poly.size()));
  }
  if (! poly[dimension])
  {
    // XXX compute poly for dimension
  }
  return *poly[dimension];
}

Rect Bezier::get_control_point_bounding_box()
{
  if (cp_bounding_box.empty())
  {
    cp_bounding_box.add_points(p);
    std::cout << "Bezier control point bounding box " << cp_bounding_box << "\n";
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

  Rect bb(p[0].dimensionality(), p);

  return bb;
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
