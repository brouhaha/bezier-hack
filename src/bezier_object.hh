// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef BEZIER_OBJECT_HH
#define BEZIER_OBJECT_HH

#include <iostream>
#include <memory>
#include <span>
#include <vector>

#include <QObject>

#include "point.hh"
#include "rect.hh"
#include "polygon.hh"
#include "bezier.hh"


class BezierObject: public QObject
{
  Q_OBJECT

public:
  BezierObject(const Bezier& bezier);

  unsigned order() const;

  Point get(unsigned control_point_index) const;

  void set(unsigned control_point_index, Point& point);

  double get(unsigned control_point_index,
	     unsigned dimension) const;

  void set(unsigned control_point_index,
	   unsigned dimension,
	   double value);

  Rect get_control_point_bounding_box();
  Rect get_bounding_box();
  Polygon get_control_point_convex_hull();

signals:
  void value_changed();

private:
  Bezier bezier;
};

#endif // BEZIER_OBJECT_HH
