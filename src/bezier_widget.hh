// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef BEZIER_WIDGET_HH
#define BEZIER_WIDGET_HH

class QHBoxLayout;
class QVBoxLayout;
#include <QWidget>

class Bezier;
class BezierGraph;
class BezierParams;

class BezierWidget : public QWidget
{
  Q_OBJECT

public:
  BezierWidget(Bezier& bezier,
	       QWidget* parent = nullptr,
	       Qt::WindowFlags f = Qt::WindowFlags());

public slots:
  void on_view_graph_changed(bool visible);
  void on_view_params_changed(bool visible);

private:
  Bezier& bezier;
  BezierParams* bezier_params;
  BezierGraph* bezier_graph;

  QHBoxLayout* hbox;
  QVBoxLayout* vbox;
};

#endif // BEZIER_WIDGET_HH
