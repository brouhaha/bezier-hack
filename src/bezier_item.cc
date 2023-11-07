// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <exception>
#include <format>

#include <QPainterPath>

#include "bezier_object.hh"
#include "bezier_item.hh"

BezierItem::BezierItem(BezierObject& bezier,
		       QGraphicsItem* parent):
  GraphicsPathObject(parent),
  bezier(bezier)
{
  setPen(QPen(Qt::black));
  setBrush(Qt::NoBrush);
  on_bezier_changed();

  connect(&bezier, &BezierObject::value_changed,
	  this,    &BezierItem::on_bezier_changed);
}

void BezierItem::on_bezier_changed()
{
  QPainterPath pp;

  pp.moveTo(bezier.get(0, X), bezier.get(0, Y));

  switch (bezier.order())
  {
  case 2:
    pp.quadTo(bezier.get(1, X), bezier.get(1, Y),
	      bezier.get(2, X), bezier.get(2, Y));
    break;
  case 3:
    pp.cubicTo(bezier.get(1, X), bezier.get(1, Y),
	       bezier.get(2, X), bezier.get(2, Y),
	       bezier.get(3, X), bezier.get(3, Y));
    break;
  default:
    throw std::runtime_error(std::format("only quadratic and cubic bezier supported, not order {}", bezier.order()));
  }

  setPath(pp);
}
