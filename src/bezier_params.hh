// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef BEZIER_PARAMS_HH
#define BEZIER_PARAMS_HH

#include <QGridLayout>
#include <QWidget>

#include "bezier_object.hh"

class DoubleLineEdit;

class BezierParams: public QWidget
{
  Q_OBJECT

public:
  BezierParams(BezierObject& bezier,
	       QWidget* parent = nullptr);

public slots:
  void on_bezier_changed();

private slots:
  void on_double_value_changed(int ref, double value);  // received from a DoubleLineEdit

private:
  BezierObject& bezier;
  QGridLayout* layout;
  DoubleLineEdit* x_coord_le[4];
  DoubleLineEdit* y_coord_le[4];
};

#endif // BEZIER_PARAMS_HH
