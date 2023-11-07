// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef RECT_ITEM_HH
#define RECT_ITEM_HH

#include <QColor>

#include "rect.hh"
#include "graphics_path_object.hh"

class RectItem: public GraphicsPathObject
{
  Q_OBJECT

public:
  RectItem(QColor color = QColor(Qt::black),
	   QGraphicsItem* parent = nullptr);

  void set_rect(Rect& r);
  void set_color(QColor color);
};

#endif // RECT_ITEM_HH
