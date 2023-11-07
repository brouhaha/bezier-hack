// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef BEZIER_ITEM_HH
#define BEZIER_ITEM_HH

#include "graphics_path_object.hh"

class BezierObject;

class BezierItem: public GraphicsPathObject
{
  Q_OBJECT

public:
  BezierItem(BezierObject& bezier,
	     QGraphicsItem* parent = nullptr);

public slots:
  void on_bezier_changed();  // received when the params values are edited

private:
  BezierObject& bezier;
};

#endif // BEZIER_ITEM_HH
