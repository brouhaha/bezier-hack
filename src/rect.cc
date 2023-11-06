// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <algorithm>
#include <exception>
#include <exception>
#include <limits>

#include "rect.hh"

Rect::Rect(int dimensionality):
  min(dimensionality),
  max(dimensionality)
{
  reset_min_max();
}

Rect::Rect(int dimensionality, std::span<Point> points):
  min(dimensionality),
  max(dimensionality)
{
  reset_min_max();
  for (auto p: points)
  {
    add_point(p);
  }
}

Rect::Rect(int dimensionality, std::initializer_list<Point> points):
  min(dimensionality),
  max(dimensionality)
{
  reset_min_max();
  for (auto p: points)
  {
    add_point(p);
  }
}

void Rect::reset_min_max()
{
  for (int i = 0; i < min.dimensionality(); i++)
  {
    min[i] =  std::numeric_limits<double>::infinity();
    max[i] = -std::numeric_limits<double>::infinity();
  }
}

void Rect::add_point(Point p)
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


