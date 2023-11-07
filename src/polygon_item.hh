// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef POLYGON_ITEM_HH
#define POLYGON_ITEM_HH

#include <initializer_list>
#include <span>

#include <QColor>

#include "point.hh"
#include "polygon.hh"
#include "graphics_path_object.hh"

class PolygonItem: public GraphicsPathObject
{
  Q_OBJECT

public:
  PolygonItem(QColor color = QColor(Qt::black),
	      QGraphicsItem* parent = nullptr);

  void set_polygon(const Polygon& polygon);

  void set_points(std::span<const Point> points);
  void set_points(std::initializer_list<Point> points);

  void set_color(QColor color);
};

#endif // POLYGON_ITEM_HH
