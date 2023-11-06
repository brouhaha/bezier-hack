// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <algorithm>
#include <limits>

#include "bezier.hh"


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

Bezier::Bezier(std::vector<Point> p):
  p(p)
{
  validate_order();
}

Bezier::Bezier(std::initializer_list<Point> p):
  p(p)
{
  validate_order();
}

Bezier::Bezier(const Bezier& b):
  p(b.p)
{
}

int Bezier::order()
{
  return p.size() - 1;
}

void Bezier::validate_order()
{
  if (order() < 2)
  {
    throw std::runtime_error(std::format("Bezier curve order ({}) must 2 or higher", order()));
  }
}

Point& Bezier::operator[] (std::size_t idx)
{
  return p[idx];
}

void Bezier::flush_cached_data()
{
  x_poly = nullptr;
  y_poly = nullptr;
}

Polynomial<double> Bezier::get_x_poly()
{
  if (! x_poly)
  {
    // XXX compute x_poly
  }
  return *x_poly;
}

Polynomial<double> Bezier::get_y_poly()
{
  if (! y_poly)
  {
    // XXX compute y_poly
  }
  return *y_poly;
}

Rect Bezier::get_bounding_box()
{
  // https://floris.briolas.nl/floris/2009/10/bounding-box-of-cubic-bezier/
  // https://stackoverflow.com/questions/24809978/calculating-the-bounding-box-of-cubic-bezier-curve

  return BoundingBox(p[0], p[3]);  // XXX wrong
}

std::ostream& operator<<(std::ostream& os, const Bezier& cb)
{
  auto it = cb.p.cbegin();
  os << "Bezier(" << *it++;
  while (it != cb.p.cend())
  {
    os << ", " << *it++;
  }
  os << ")";
  return os;
}
