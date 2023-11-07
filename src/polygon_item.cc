// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QBrush>
#include <QPen>

#include "polygon_item.hh"

PolygonItem::PolygonItem(QColor color,
			 QGraphicsItem* parent):
  GraphicsPathObject(parent)
{
  setBrush(Qt::NoBrush);
  set_color(color);
}

void PolygonItem::set_polygon(const Polygon& polygon)
{
  set_points(polygon.get_points());
}

void PolygonItem::set_points(std::span<const Point> points)
{
  QPainterPath pp;

  QPolygonF poly;

  for (auto p: points)
  {
    poly << QPointF(p[X], p[Y]);
  }
  pp.addPolygon(poly);
  pp.closeSubpath();
  setPath(pp);
}

void PolygonItem::set_points(std::initializer_list<Point> points)
{
  std::span span(points.begin(), points.size());
  set_points(span);
}

void PolygonItem::set_color(QColor color)
{
  setPen(color);
}
