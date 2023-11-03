// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <algorithm>
#include <limits>

#include "cubic_bezier.hh"


std::ostream& operator<<(std::ostream& os, const Point& p)
{
  return os << "Point(" << p.x << ", " << p.y << ")";
}


Rect::Rect(Point top_left, Point bottom_right):
  top_left(top_left),
  bottom_right(bottom_right)
{
}


BoundingBox::BoundingBox():
  Rect(Point( std::numeric_limits<double>::infinity(),
	      std::numeric_limits<double>::infinity()),
       Point(-std::numeric_limits<double>::infinity(),
	     -std::numeric_limits<double>::infinity()))
{
}

BoundingBox::BoundingBox(Rect r):
  Rect(r)
{
  if (top_left.x > bottom_right.x)
    std::swap<double>(top_left.x, bottom_right.x);
  if (top_left.y > bottom_right.y)
    std::swap<double>(top_left.y, bottom_right.y);
}

BoundingBox::BoundingBox(Point p0, Point p1):
  Rect(p0, p1)
{
  if (top_left.x > bottom_right.x)
    std::swap<double>(top_left.x, bottom_right.x);
  if (top_left.y > bottom_right.y)
    std::swap<double>(top_left.y, bottom_right.y);
}

BoundingBox& BoundingBox::operator+(Rect& other)
{
  top_left.x = std::min(top_left.x, other.top_left.x);
  top_left.y = std::min(top_left.y, other.top_left.y);
  bottom_right.x = std::max(bottom_right.x, other.bottom_right.x);
  bottom_right.y = std::max(bottom_right.y, other.bottom_right.y);

  return *this;
}

CubicBezier::CubicBezier(std::array<Point, 4> p):
  p(p)
{
}

CubicBezier::CubicBezier(Point p0, Point p1, Point p2, Point p3):
  p { p0, p1, p2, p3 }
{
}

Rect CubicBezier::get_bounding_box()
{
  return BoundingBox(p[0], p[3]);  // XXX wrong
}

std::ostream& operator<<(std::ostream& os, const CubicBezier& cb)
{
  return os << "CubicBezier(" << cb.p[0] << ", " << cb.p[1] << ", " << cb.p[2] << ", " << cb.p[3] << ")";
}
