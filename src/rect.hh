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
  Rect(unsigned dimensionality);
  Rect(unsigned dimensionality, const std::span<Point> points);
  Rect(unsigned dimensionality, const std::initializer_list<Point> points);

  void reset();

  bool empty();

  void add_points(const std::span<Point> points);
  void add_points(const std::initializer_list<Point> points);
  void add_point(const Point p);
  
  double get_min_coordinate(unsigned dimension);
  double get_max_coordinate(unsigned dimension);
  double get_extent(unsigned dimension);

  friend std::ostream& operator<< (std::ostream& os, const Rect& r);

private:
  unsigned dimensionality;

  Point min;
  Point max;
};

#endif // RECT_HH
