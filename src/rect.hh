// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef RECT_HH
#define RECT_HH

#include <initializer_list>
#include <span>

#include "point.hh"

class Rect
{
public:
  Rect(int dimensionality);
  Rect(int dimensionality, std::span<Point> points);
  Rect(int dimensionality, std::initializer_list<Point> points);

  void add_point(Point p);
  
  friend std::ostream& operator<< (std::ostream& os, const Rect& r);

private:
  Point min;
  Point max;

  void reset_min_max();
};

#endif // RECT_HH
