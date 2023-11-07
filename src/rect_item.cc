// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QBrush>
#include <QPen>

#include "rect_item.hh"

RectItem::RectItem(QColor color,
		   QGraphicsItem* parent):
  GraphicsPathObject(parent)
{
  setBrush(Qt::NoBrush);
  set_color(color);
}

void RectItem::set_rect(Rect& r)
{
  setPos(r.get_min_coordinate(X) + r.get_extent(X) / 2.0,
	 r.get_min_coordinate(Y) + r.get_extent(Y) / 2.0);

  QPainterPath pp;
  if (! r.empty())
  {
    pp.addRect(-r.get_extent(X) / 2.0,
	       -r.get_extent(Y) / 2.0,
	       r.get_extent(X),
	       r.get_extent(Y));
  }
  setPath(pp);
}

void RectItem::set_color(QColor color)
{
  setPen(color);
}
