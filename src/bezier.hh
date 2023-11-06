// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef BEZIER_HH
#define BEZIER_HH

#include <initializer_list>
#include <iostream>
#include <memory>
#include <vector>

#include "polynomial.hh"


class Point
{
public:
  double x;
  double y;

  friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

class Rect
{
public:
  Rect(Point top_left, Point bottom_right);
  
  Point top_left;
  Point bottom_right;
};

class BoundingBox: public Rect
{
public:
  BoundingBox();  // empty bounding box
  BoundingBox(Point p0, Point p1);
  BoundingBox(Rect r);
  BoundingBox& operator+(Rect& other);
};


class Bezier
{
public:
  Bezier(std::vector<Point> p);
  Bezier(std::initializer_list<Point> p);
  Bezier(const Bezier& b);

  int order();

  Point& operator[] (std::size_t idx);

  Polynomial<double> get_x_poly();
  Polynomial<double> get_y_poly();

  Rect get_bounding_box();

  friend std::ostream& operator<<(std::ostream& os, const Bezier& cb);

private:
  std::vector<Point> p;

  std::unique_ptr<Polynomial<double>> x_poly;
  std::unique_ptr<Polynomial<double>> y_poly;

  void validate_order();
  void flush_cached_data();

  friend class PointWriteProxy;
};

#endif // BEZIER_BEZIER_HH
