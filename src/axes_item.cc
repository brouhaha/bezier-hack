// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <iostream>

#include <QPainter>
#include <QRectF>

#include "axes_item.hh"

AxesItem::AxesItem(double min_coord,
		   double max_coord,
		   double grid_spacing,
		   QGraphicsItem* parent):
  QGraphicsItem(parent),
  min_coord(min_coord),
  max_coord(max_coord),
  grid_spacing(grid_spacing)
{
}

QRectF AxesItem::boundingRect() const
{
  return QRectF(min_coord-35.0, min_coord-35.0, max_coord+35.0, max_coord+35.0);
}

void AxesItem::paint(QPainter* painter,
		     const QStyleOptionGraphicsItem* option,
		     QWidget* widget)
{
  //painter->setRenderHint(QPainter::Antialiasing);

  QColor black(0, 0, 0);
  QColor gray(192, 192, 192);

#if 1
  QColor white(255, 255, 255);
  painter->setPen(white);
  painter->drawRect(min_coord-35.0, min_coord-35.0,
		    (max_coord-min_coord) + 70.0,
		    (max_coord-min_coord) + 70.0);
#endif

  painter->setPen(black);
  painter->setBrush(Qt::NoBrush);  // don't want fill
  painter->drawRect(min_coord, min_coord, max_coord-min_coord, max_coord-min_coord);

  QFont font = painter->font();
  font.setPointSize(6);
  painter->setFont(font);

  for (int i = min_coord; i <= max_coord; i += grid_spacing)
  {
    painter->drawLine(min_coord-7,           i, min_coord-3,           i);
    painter->drawLine(max_coord+3,           i, max_coord+7,           i);
    painter->drawLine(          i, min_coord-7,           i, min_coord-3);
    painter->drawLine(          i, max_coord+3,           i, max_coord+7);

    QString s;
    s.setNum(i);
    {
      QRectF r(min_coord-32, i-5, 17, 10);
      painter->drawText(r, Qt::AlignRight | Qt::AlignVCenter, s);
    }
    {
      QRectF r(max_coord+15, i-5, 17, 10);
      painter->drawText(r, Qt::AlignLeft | Qt::AlignVCenter, s);
    }

    painter->save();
    painter->rotate(-90.0);
    {
      QRectF r(min_coord-32, i-5, 17, 10);
      painter->drawText(r, Qt::AlignRight | Qt::AlignVCenter, s);
    }
    {
      QRectF r(max_coord+15, i-5, 17, 10);
      painter->drawText(r, Qt::AlignLeft | Qt::AlignVCenter, s);
    }
    painter->restore();
  }

  painter->setPen(gray);
  for (int i = min_coord; i <= max_coord; i += grid_spacing / 4.0)
  {
    for (int j = min_coord; j <= max_coord; j += grid_spacing / 4.0)
    {
      painter->drawPoint(i, j);
    }
  }
}
