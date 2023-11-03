// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef CUBIC_BEZIER_HH
#define CUBIC_BEZIER_HH

#include <array>
#include <iostream>

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

class CubicBezier
{
public:
  CubicBezier(std::array<Point, 4> p);
  CubicBezier(Point p0, Point p1, Point p2, Point p3);

  std::array<Point, 4> p;
  // p[0] is start point
  // p[1] and p[2] are control points
  // p[3] is end point

  Rect get_bounding_box();

  friend std::ostream& operator<<(std::ostream& os, const CubicBezier& cb);
};

#endif // CUBIC_BEZIER_HH
