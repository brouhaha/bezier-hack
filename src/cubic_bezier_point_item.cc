// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <iostream>

#include <QGraphicsSceneDragDropEvent>
#include <QPen>

#include "cubic_bezier_point_item.hh"

CubicBezierPointItem::CubicBezierPointItem(bool endpoint,
					   QGraphicsItem* parent):
  QGraphicsRectItem(parent)
{
  setPen(QPen(Qt::NoPen));
  setBrush(endpoint ? Qt::green : Qt::blue);
  setFlag(QGraphicsItem::ItemIsMovable);
  setAcceptDrops(true);
}

void CubicBezierPointItem::on_position_changed(double x, double y)
{
  std::cout << "on_position_changed(" << x << ", " << y << ")\n";
  setRect(x - point_size / 2.0,
	  y - point_size / 2.0,
	  point_size,
	  point_size);
}

void CubicBezierPointItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
  std::cout << "dragEnterEvent()\n";
  event->setAccepted(true);
}

void CubicBezierPointItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
  std::cout << "dragDropEvent()\n";
}

