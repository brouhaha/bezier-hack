// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef CUBIC_BEZIER_ITEM_HH
#define CUBIC_BEZIER_ITEM_HH

#include <QGraphicsPathItem>

class CubicBezier;

class CubicBezierItem: public QGraphicsPathItem
{
  Q_OBJECT

public:
  CubicBezierItem(CubicBezier& cb,
		  QGraphicsItem* parent = nullptr);

private:
  CubicBezier& cb;
  QPainterPath path;
};

#endif // CUBIC_BEZIER_ITEM_HH
