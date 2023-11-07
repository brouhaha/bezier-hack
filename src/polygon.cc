// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <algorithm>
#include <exception>
#include <format>

#include "polygon.hh"

Polygon::Polygon(std::span<const Point> points)
{
  set_points(points);
}

Polygon::Polygon(std::initializer_list<Point> points)
{
  std::span span(points.begin(), points.size());
  set_points(span);
}


void Polygon::set_points(std::span<const Point> points)
{
  this->points.assign(points.begin(), points.end());
}


std::span<const Point> Polygon::get_points() const
{
  return points;
}


static double three_point_orientation(const Point& p, const Point& q, const Point& r)
{
  return (q[X] - p[X]) * (r[Y] - q[Y]) - (q[Y] - p[Y]) * (r[X] - q[X]);
}


Polygon Polygon::convex_hull() const
{
  switch (points.size())
  {
  case 3:
    return *this;

  case 4:
    {
      // https://stackoverflow.com/a/2122620
      // https://stackoverflow.com/a/56417735
      double abc = three_point_orientation(points[0], points[1], points[2]);
      double bcd = three_point_orientation(points[1], points[2], points[3]);
      double cda = three_point_orientation(points[2], points[3], points[0]);
      double dab = three_point_orientation(points[3], points[0], points[1]);
      if ((abc == 0) || (bcd == 0) || (cda == 0) || (dab == 0))
      {
	throw std::runtime_error("no hull");
      }
      switch ((abc > 0) * 8 + (bcd > 0) * 4 + (cda > 0) * 2 + (dab > 0))
      {
      case 0b0000:  // ----  adcb
	return Polygon {points[0], points[3], points[2], points[1]};
      case 0b0001:  // ---+ bdc
	return Polygon {points[1], points[3], points[2]};
      case 0b0010:  // --+- acb
	return Polygon {points[0], points[2], points[1]};
      case 0b0011:  // --++ acbd
	return Polygon {points[0], points[2], points[1], points[3]};
      case 0b0100:  // -+-- adb
	return Polygon {points[0], points[3], points[1]};
      case 0b0101:  // -+-+
	throw std::runtime_error("hull failure");
      case 0b0110:  // -++- acdb
	return Polygon {points[0], points[2], points[3], points[1]};
      case 0b0111:  // -+++ acd
	return Polygon {points[0], points[2], points[3]};
      case 0b1000:  // +---  adc
	return Polygon {points[0], points[3], points[2]};
      case 0b1001:  // +--+  abdc
	return Polygon {points[0], points[1], points[3], points[2]};
      case 0b1010:  // +-+-
	throw std::runtime_error("hull failure");
      case 0b1011:  // +-++  abd
	return Polygon {points[0], points[1], points[3]};
      case 0b1100:  // ++--  adbc
	return Polygon {points[0], points[3], points[1], points[2]};
      case 0b1101:  // ++-+  abc
	return Polygon {points[0], points[1], points[2]};
      case 0b1110:  // +++-  bcd
	return Polygon {points[1], points[2], points[3]};
      case 0b1111:  // ++++  abcd
	return Polygon {points[0], points[1], points[2], points[3]};
      }
    }

  default:
    throw std::runtime_error(std::format("convex hull of {} points is not implemented", points.size()));
  }
}
