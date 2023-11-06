// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef CUBIC_BEZIER_WIDGET_HH
#define CUBIC_BEZIER_WIDGET_HH

class QHBoxLayout;
class QVBoxLayout;
#include <QWidget>

class CubicBezier;
class CubicBezierGraph;
class CubicBezierParams;

class CubicBezierWidget : public QWidget
{
  Q_OBJECT

public:
  CubicBezierWidget(CubicBezier& cb,
		    QWidget* parent = nullptr,
		    Qt::WindowFlags f = Qt::WindowFlags());

private:
  CubicBezier& cb;
  CubicBezierParams *cbp;
  CubicBezierGraph* cbg;

  QHBoxLayout* hbox;
  QVBoxLayout* vbox;
};

#endif // CUBIC_BEZIER_WIDGET_HH
