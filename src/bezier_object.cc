// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include "bezier_object.hh"


BezierObject::BezierObject(const Bezier& bezier):
  bezier(bezier)
{
}

unsigned BezierObject::order() const
{
  return bezier.order();
}

Point BezierObject::get(unsigned control_point_index) const
{
  return bezier.get(control_point_index);
}

void BezierObject::set(unsigned control_point_index, Point& point)
{
  if (point != bezier.get(control_point_index))
  {
    bezier.set(control_point_index, point);
    emit value_changed();
  }
}

double BezierObject::get(unsigned control_point_index,
			 unsigned dimension) const
{
  return bezier.get(control_point_index, dimension);
}

void BezierObject::set(unsigned control_point_index,
		       unsigned dimension,
		       double value)
{
  if (value != bezier.get(control_point_index, dimension))
  {
    bezier.set(control_point_index, dimension, value);
    emit value_changed();
  }
}

Rect BezierObject::get_control_point_bounding_box()
{
  return bezier.get_control_point_bounding_box();
}

Rect BezierObject::get_bounding_box()
{
  return bezier.get_bounding_box();
}

Polygon BezierObject::get_control_point_convex_hull()
{
  return bezier.get_control_point_convex_hull();
}
