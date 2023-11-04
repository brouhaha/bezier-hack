// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QGraphicsSceneDragDropEvent>
#include <QPen>

#include "point_item.hh"

static constexpr double default_diamter = 4.0;


PointItem::PointItem(int point_id,
		     QGraphicsItem* parent):
  GraphicsPathObject(parent),
  m_point_id(point_id)
{
  setPen(QPen(Qt::NoPen));
  set_diameter(default_diamter);
  set_color(QColor(Qt::black));

  setFlag(QGraphicsItem::ItemIsMovable);

  connect(this, &QGraphicsObject::xChanged,
	  this, &PointItem::on_coordinate_changed);
}

int PointItem::point_id()
{
  return m_point_id;
}

void PointItem::set_point_id(int point_id)
{
  m_point_id = point_id;
}

void PointItem::set_diameter(double diameter)
{
  QPainterPath pp;
  pp.addEllipse(QPointF(), diameter/2.0, diameter/2.0);
  setPath(pp);
}

void PointItem::set_color(QColor color)
{
  setBrush(color);
}

void PointItem::on_position_changed(double x, double y)
{
  setPos(x, y);
}

// for signals xChanged() and yChanged from superclass (QGraphicsObject)
void PointItem::on_coordinate_changed()
{
  emit position_changed(m_point_id, x(), y());
}
