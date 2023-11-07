// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef POLYGON_HH
#define POLYGON_HH

#include <initializer_list>
#include <span>
#include <vector>

#include "point.hh"

class Polygon
{
public:
  Polygon(std::span<const Point> points);
  Polygon(std::initializer_list<Point> points);

  std::span<const Point> get_points() const;

  Polygon convex_hull() const;

private:
  std::vector<Point> points;

  void set_points(std::span<const Point> points);
};

#endif // POLYGON_HH
