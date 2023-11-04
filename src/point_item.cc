// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <iostream>

#include <QGraphicsSceneDragDropEvent>
#include <QPen>

#include "point_item.hh"

static constexpr double default_diamter = 4.0;


PointItem::PointItem(QGraphicsItem* parent):
  QGraphicsEllipseItem(parent)
{
  setPen(QPen(Qt::NoPen));
  set_diameter(default_diamter);
  set_color(QColor(Qt::black));
  setFlag(QGraphicsItem::ItemIsMovable);
  setAcceptDrops(true);
}

void PointItem::set_diameter(double diameter)
{
  setRect(-diameter/2.0, -diameter/2.0,
	  diameter, diameter);
}

void PointItem::set_color(QColor color)
{
  setBrush(color);
}

void PointItem::on_position_changed(double x, double y)
{
  std::cout << "on_position_changed(" << x << ", " << y << ")\n";
  setPos(x, y);
}

void PointItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
  std::cout << "dragEnterEvent()\n";
  event->setAccepted(true);
}

void PointItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
  std::cout << "dragDropEvent()\n";
}

