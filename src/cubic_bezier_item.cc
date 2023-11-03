// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QPainter>
#include <QPainterPath>

#include "cubic_bezier.hh"
#include "cubic_bezier_item.hh"

CubicBezierItem::CubicBezierItem(CubicBezier& cb,
				 QGraphicsItem* parent):
  QGraphicsItem(parent),
  cb(cb)
{
}

QRectF CubicBezierItem::boundingRect() const
{
  return QRectF(-135.0, -135.0, 270.0, 270.0);  // XXX compute this!
}

void CubicBezierItem::paint(QPainter* painter,
			    const QStyleOptionGraphicsItem* option,
			    QWidget* widget)
{
  QColor black(0, 0, 0);
  painter->setPen(black);
  painter->setBrush(Qt::NoBrush);  // don't want fill

  QPainterPath cb_path;
  cb_path.moveTo(cb.p[0].x, cb.p[0].y);
  cb_path.cubicTo(cb.p[1].x, cb.p[1].y,
		  cb.p[2].x, cb.p[2].y,
		  cb.p[3].x, cb.p[3].y);
  painter->drawPath(cb_path);
}
