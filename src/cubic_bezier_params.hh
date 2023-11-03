// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef CUBIC_BEZIER_PARAMS_HH
#define CUBIC_BEZIER_PARAMS_HH

#include <QGridLayout>
#include <QWidget>

#include "cubic_bezier.hh"

class CubicBezier;
class DoubleLineEdit;

class CubicBezierParams: public QWidget
{
  Q_OBJECT

public:
  CubicBezierParams(CubicBezier& cb,
		    QWidget* parent = nullptr);

public slots:
  void on_cubic_bezier_changed();  // recieved when user drags handles

signals:
  void cubic_bezier_changed();  // emitted when user edits a numerc value

private slots:
  void on_double_value_changed(double value);  // received from a DoubleLineEdit

private:
  CubicBezier& cb;
  CubicBezier prev_cb;
  QGridLayout* layout;
  DoubleLineEdit* x_coord_le[4];
  DoubleLineEdit* y_coord_le[4];
};

#endif // CUBIC_BEZIER_PARAMS_HH
