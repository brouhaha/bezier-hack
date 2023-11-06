// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <algorithm>
#include <limits>

#include "bezier.hh"


Bezier::Bezier(std::span<Point> control_points)
{
  validate_order();
  p.assign(control_points.begin(), control_points.end());
}

Bezier::Bezier(std::initializer_list<Point> control_points):
  p(control_points)
{
  validate_order();
}

Bezier::Bezier(const Bezier& b):
  p(b.p)
{
}

int Bezier::order()
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

Point& Bezier::operator[] (std::size_t idx)
{
  return p[idx];
}

void Bezier::flush_cached_data()
{
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
