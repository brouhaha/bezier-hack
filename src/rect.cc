// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <algorithm>
#include <cmath>
#include <exception>
#include <exception>
#include <limits>

#include "rect.hh"

Rect::Rect(unsigned dimensionality):
  dimensionality(dimensionality),
  min(dimensionality),
  max(dimensionality)
{
  reset();
}

Rect::Rect(unsigned dimensionality, const std::span<Point> points):
  dimensionality(dimensionality),
  min(dimensionality),
  max(dimensionality)
{
  reset();
  for (auto p: points)
  {
    add_point(p);
  }
}

Rect::Rect(unsigned dimensionality, const std::initializer_list<Point> points):
  dimensionality(dimensionality),
  min(dimensionality),
  max(dimensionality)
{
  reset();
  for (auto p: points)
  {
    add_point(p);
  }
}

void Rect::reset()
{
  for (int i = 0; i < dimensionality; i++)
  {
    min[i] =  std::numeric_limits<double>::infinity();
    max[i] = -std::numeric_limits<double>::infinity();
  }
}

bool Rect::empty()
{
  for (unsigned dimension = 0; dimension < dimensionality; dimension++)
  {
    if (std::isinf(min[dimension]) ||
	std::isinf(max[dimension]) ||
	(get_extent(dimension) <= 0.0))
      return true;
  }
  return false;
}

double Rect::get_min_coordinate(unsigned dimension)
{
  return min[dimension];
}

double Rect::get_max_coordinate(unsigned dimension)
{
  return max[dimension];
}

double Rect::get_extent(unsigned dimension)
{
  return max[dimension] - min[dimension];
}

void Rect::add_points(const std::span<Point> points)
{
  for (auto p: points)
  {
    add_point(p);
  }
}

void Rect::add_points(const std::initializer_list<Point> points)
{
  for (auto p: points)
  {
    add_point(p);
  }
}

void Rect::add_point(const Point p)
{
  if (min.dimensionality() != p.dimensionality())
  {
    throw std::runtime_error("points added to rectangle have non-matching dimensionality");
  }

  for (int i = 0; i < p.dimensionality(); i++)
  {
    if (p[i] < min[i])
      min[i] = p[i];
    if (p[i] > max[i])
      max[i] = p[i];
  }
}

std::ostream& operator<< (std::ostream& os, const Rect& r)
{
  os << "Rect(" << r.min << ", " << r.max << ")";
  return os;
}


#if 0
int main(int argc, char* argv[])
{
  Rect r1(2, {{ 3.3, 4.4 }, { 5.5, 6.6 }});
  std::cout << r1 << "\n";

  Rect r2(3, {{ 3.3, 4.4, 5.5 }, { 6.6, 7.7, 8.8 }});
  std::cout << r2 << "\n";

  return 0;
}
#endif


