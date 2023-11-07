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
#include "polygon.hh"
#include "polynomial.hh"


class Bezier
{
public:
  Bezier(std::span<Point> control_points);
  Bezier(std::initializer_list<Point> control_points);
  Bezier(const Bezier& b);

  bool operator==(const Bezier& other) const;

  Bezier& operator=(const Bezier& other);

  int order() const;

  std::span<const Point> get() const;  // get all control points

  const Point& get(std::size_t idx) const;  // get one control point

  void set(std::size_t idx, const Point& point);  // set one control point

  const double get(std::size_t idx, unsigned dimension) const;  // get one coordinate of one control point

  void set(std::size_t idx, unsigned dimension, double value);  // set one coordinate of one control point

  Rect get_control_point_bounding_box();
  Rect get_bounding_box();
  Polygon get_control_point_convex_hull();

  friend std::ostream& operator<<(std::ostream& os, const Bezier& cb);

private:
  std::vector<Point> p;

  Rect cp_bounding_box;
  std::unique_ptr<Polygon> cp_convex_hull;
  Rect bounding_box;

  void validate_order();
  void flush_cached_data();

  Polynomial compute_polynomial(unsigned dimension);
};

#endif // BEZIER_HH
