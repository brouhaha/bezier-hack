// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QPainterPath>

#include "cubic_bezier.hh"
#include "cubic_bezier_item.hh"

CubicBezierItem::CubicBezierItem(CubicBezier& cb,
				 QGraphicsItem* parent):
  GraphicsPathObject(parent),
  cb(cb)
{
  setPen(QPen(Qt::black));
  setBrush(Qt::NoBrush);
  on_cubic_bezier_changed();
}

void CubicBezierItem::on_cubic_bezier_changed()
{
  QPainterPath pp;

  pp.moveTo(cb.p[0].x, cb.p[0].y);
  pp.cubicTo(cb.p[1].x, cb.p[1].y,
	     cb.p[2].x, cb.p[2].y,
	     cb.p[3].x, cb.p[3].y);
  setPath(pp);
}
