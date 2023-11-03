// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef AXES_ITEM_HH
#define AXES_ITEM_HH

#include <QGraphicsItem>

class AxesItem: public QGraphicsItem
{
public:
  AxesItem(double min_coord,
	   double max_coord,
	   double grid_spacing,
	   QGraphicsItem* parent = nullptr);

  QRectF boundingRect() const override;

  void paint(QPainter* painter,
	     const QStyleOptionGraphicsItem* option,
	     QWidget* widget = nullptr) override;

private:
  double min_coord;
  double max_coord;
  double grid_spacing;
};

#endif // AXES_ITEM_HH
