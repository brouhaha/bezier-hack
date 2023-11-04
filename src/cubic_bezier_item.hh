// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef CUBIC_BEZIER_ITEM_HH
#define CUBIC_BEZIER_ITEM_HH

#include "graphics_path_object.hh"

class CubicBezier;

class CubicBezierItem: public GraphicsPathObject
{
public:
  CubicBezierItem(CubicBezier& cb,
		  QGraphicsItem* parent = nullptr);

  QRectF boundingRect() const override;

  void paint(QPainter* painter,
	     const QStyleOptionGraphicsItem* option,
	     QWidget* widget) override;

private:
  CubicBezier& cb;
};

#endif // CUBIC_BEZIER_ITEM_HH
