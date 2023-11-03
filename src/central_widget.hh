// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef CENTRAL_WIDGET_HH
#define CENTRAL_WIDGET_HH

class QHBoxLayout;
class QVBoxLayout;
#include <QWidget>

class CubicBezier;
class CubicBezierView;
class CubicBezierParams;

class CentralWidget : public QWidget
{
  Q_OBJECT

public:
  CentralWidget(CubicBezier& cb,
		QWidget* parent = nullptr,
		Qt::WindowFlags f = Qt::WindowFlags());

private:
  CubicBezier& cb;
  CubicBezierParams *cbp;
  CubicBezierView* cbv;

  QHBoxLayout* hbox;
  QVBoxLayout* vbox;
};

#endif // CENTRAL_WIDGET_HH
