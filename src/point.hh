// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef POINT_HH
#define POINT_HH

#include <initializer_list>
#include <iostream>
#include <span>
#include <vector>


enum Dimension
{
  X = 0,
  Y = 1,
  Z = 2,
  // no specific names for higher dimensions
};

class Point
{
public:
  Point(int dimensionality);  // construct an invalid point

  Point(std::span<double> coordinates);
  
  Point(std::initializer_list<double> coordinates);

  unsigned dimensionality();

  std::span<double> get();

  double& operator[] (size_t dimension);

  friend std::ostream& operator<< (std::ostream& os, const Point& p);

private:
  std::vector<double> c;
};

#endif // POINT_HH
