// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef BEZIER_HH
#define BEZIER_HH

#include <initializer_list>
#include <iostream>
#include <memory>
#include <span>
#include <vector>

#include "point.hh"
#include "rect.hh"
#include "polynomial.hh"


class Bezier
{
public:
  Bezier(std::span<Point> control_points);
  Bezier(std::initializer_list<Point> control_points);
  Bezier(const Bezier& b);

  int order();

  Point& operator[] (std::size_t idx);

  Polynomial get_poly(unsigned dimension);

  Rect get_bounding_box();

  friend std::ostream& operator<<(std::ostream& os, const Bezier& cb);

private:
  std::vector<Point> p;

  std::vector<std::unique_ptr<Polynomial>> poly;

  void validate_order();
  void flush_cached_data();
};

#endif // BEZIER_HH
