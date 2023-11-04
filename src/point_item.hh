// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef POINT_ITEM_HH
#define POINT_ITEM_HH

#include <QColor>
#include <QGraphicsEllipseItem>

class PointItem: public QGraphicsEllipseItem
{
public:
  PointItem(QGraphicsItem* parent = nullptr);

  void set_diameter(double dimater);
  void set_color(QColor color);

public slots:
  void on_position_changed(double x, double y);

private slots:
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
  void dropEvent(QGraphicsSceneDragDropEvent *event) override;
};

#endif // POINT_ITEM_HH
