// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <exception>
#include <format>

#include <QPainterPath>

#include "bezier.hh"
#include "bezier_item.hh"

BezierItem::BezierItem(Bezier& bezier,
		       QGraphicsItem* parent):
  GraphicsPathObject(parent),
  bezier(bezier)
{
  setPen(QPen(Qt::black));
  setBrush(Qt::NoBrush);
  on_bezier_changed();
}

void BezierItem::on_bezier_changed()
{
  QPainterPath pp;

  pp.moveTo(bezier[0].x, bezier[0].y);

  switch (bezier.order())
  {
  case 2:
    pp.quadTo(bezier[1].x, bezier[1].y,
	      bezier[2].x, bezier[2].y);
    break;
  case 3:
    pp.cubicTo(bezier[1].x, bezier[1].y,
	       bezier[2].x, bezier[2].y,
	       bezier[3].x, bezier[3].y);
    break;
  default:
    throw std::runtime_error(std::format("only quadratic and cubic bezier supported, not order {}", bezier.order()));
  }

  setPath(pp);
}
