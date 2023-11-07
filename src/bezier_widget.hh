// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef BEZIER_WIDGET_HH
#define BEZIER_WIDGET_HH

class QHBoxLayout;
class QVBoxLayout;
#include <QWidget>

class BezierObject;
class BezierGraph;
class BezierParams;

class BezierWidget : public QWidget
{
  Q_OBJECT

public:
  BezierWidget(BezierObject& bezier,
	       QWidget* parent = nullptr,
	       Qt::WindowFlags f = Qt::WindowFlags());

public slots:
  void on_view_graph_changed(bool visible);
  void on_view_cp_convex_hull_changed(bool visible);
  void on_view_cp_bounding_box_changed(bool visible);
  void on_view_bezier_bounding_box_changed(bool visible);

  void on_view_params_changed(bool visible);

private:
  BezierObject& bezier;
  BezierParams* bezier_params;
  BezierGraph* bezier_graph;

  QHBoxLayout* hbox;
  QVBoxLayout* vbox;
};

#endif // BEZIER_WIDGET_HH
