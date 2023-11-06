// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <array>

#include "point.hh"

Point::Point(int dimensionality)
{
  c.assign(dimensionality, 0);
}

Point::Point(std::span<double> coordinates)
{
  c.assign(coordinates.begin(), coordinates.end());
}

Point::Point(std::initializer_list<double> coordinates):
  c(coordinates)
{
}

unsigned Point::dimensionality()
{
  return c.size();
}

std::span<double> Point::get()
{
  return c;
}

double& Point::operator[] (size_t dimension)
{
  return c[dimension];
}

std::ostream& operator<< (std::ostream& os, const Point& p)
{
  auto it = p.c.begin();
  os << "Point(" << *it++;
  while (it != p.c.cend())
  {
    os << ", " << *it++;
  }
  os << ")";
  return os;
}


#if 0
int main(int argc, char* argv[])
{
  Point p1 { 7.0, 8.2 };
  std::cout << p1 << "\n";

  Point p2 { 11.0, 12.0, 13.0 };

  std::cout << p2 << "\n";

  std::vector<double> v { 3.6, 2.9 };
  Point p3(v);
  std::cout << p3 << "\n";

  std::array<double, 3> a { 1.1, 2.2, 3.3 };
  Point p4(a);
  std::cout << p4 << "\n";

  return 0;
}
#endif


