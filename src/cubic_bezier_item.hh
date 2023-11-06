// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef CUBIC_BEZIER_ITEM_HH
#define CUBIC_BEZIER_ITEM_HH

#include "graphics_path_object.hh"

class Bezier;

class CubicBezierItem: public GraphicsPathObject
{
  Q_OBJECT

public:
  CubicBezierItem(Bezier& bezier,
		  QGraphicsItem* parent = nullptr);

public slots:
  void on_cubic_bezier_changed();  // received when the params values are edited

private:
  Bezier& bezier;
};

#endif // CUBIC_BEZIER_ITEM_HH
