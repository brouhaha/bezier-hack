// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef CUBIC_BEZIER_POINT_ITEM_HH
#define CUBIC_BEZIER_POINT_ITEM_HH

#include <QGraphicsRectItem>

class CubicBezierPointItem: public QGraphicsRectItem
{
public:
  CubicBezierPointItem(bool endpoint,
		       QGraphicsItem* parent = nullptr);

public slots:
  void on_position_changed(double x, double y);

private slots:
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
  void dropEvent(QGraphicsSceneDragDropEvent *event) override;

private:
  static constexpr double point_size = 2.0;
};

#endif // CUBIC_BEZIER_POINT_ITEM_HH
