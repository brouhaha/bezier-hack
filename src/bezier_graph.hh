// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef BEZIER_GRAPH_HH
#define BEZIER_GRAPH_HH

#include <memory>

#include <QGraphicsView>

#include "bezier_object.hh"
#include "axes_item.hh"
#include "point_item.hh"
#include "rect_item.hh"
#include "polygon_item.hh"
#include "bezier_item.hh"

class BezierGraph: public QGraphicsView
{
  Q_OBJECT

public:
  BezierGraph(BezierObject& bezier,
	      QWidget* parent = nullptr);

  void zoomToFit();

  QSize sizeHint() const override;

public slots:
  void on_bezier_changed();  // received when the params values are edited

  void on_view_cp_convex_hull_changed(bool visible);
  void on_view_cp_bounding_box_changed(bool visible);
  void on_view_bezier_bounding_box_changed(bool visible);

private slots:
  void on_point_position_changed(int point_id,
				 double x,
				 double y);

protected:
  void resizeEvent(QResizeEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

private:
  BezierObject& bezier;
  AxesItem ai;
  std::vector<std::unique_ptr<PointItem>> pi;
  BezierItem bezier_item;

  Rect cp_bounding_box;
  RectItem cp_bounding_box_item;

  PolygonItem cp_convex_hull_item;

  RectItem bezier_bounding_box_item;

  void update_cp_bounding_box();
  void update_cp_convex_hull();
};

#endif // BEZIER_GRAPH_HH
