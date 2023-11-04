// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef POINT_ITEM_HH
#define POINT_ITEM_HH

#include <QColor>

#include "graphics_path_object.hh"

class PointItem: public GraphicsPathObject
{
  Q_OBJECT

public:
  PointItem(int point_id = 0,
	    QGraphicsItem* parent = nullptr);

  int point_id();
  void set_point_id(int point_id);

  void set_diameter(double dimater);
  void set_color(QColor color);

signals:
  void position_changed(int point_id,
			double x,
			double y);

public slots:
  void on_position_changed(double x, double y);

private slots:
  void on_coordinate_changed();

private:
  int m_point_id;
};

#endif // POINT_ITEM_HH
