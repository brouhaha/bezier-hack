// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef CUBIC_BEZIER_WIDGET_HH
#define CUBIC_BEZIER_WIDGET_HH

class QHBoxLayout;
class QVBoxLayout;
#include <QWidget>

class Bezier;
class CubicBezierGraph;
class CubicBezierParams;

class CubicBezierWidget : public QWidget
{
  Q_OBJECT

public:
  CubicBezierWidget(Bezier& bezier,
		    QWidget* parent = nullptr,
		    Qt::WindowFlags f = Qt::WindowFlags());

public slots:
  void on_view_graph_changed(bool visible);
  void on_view_params_changed(bool visible);

private:
  Bezier& bezier;
  CubicBezierParams* cbp;
  CubicBezierGraph* cbg;

  QHBoxLayout* hbox;
  QVBoxLayout* vbox;
};

#endif // CUBIC_BEZIER_WIDGET_HH
