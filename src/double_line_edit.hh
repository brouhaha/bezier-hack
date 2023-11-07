// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef DOUBLE_LINE_EDIT_HH
#define DOUBLE_LINE_EDIT_HH

#include <QLineEdit>

class DoubleLineEdit: public QLineEdit
{
  Q_OBJECT

public:
  DoubleLineEdit(int ref,
		 double value = 0.0,
		 QWidget* parent = nullptr);

signals:
  void value_changed(int ref, double value);  // emitted when user edits a numeric value

public slots:
  void on_value_changed(double value);  // received from BezierParams when the bezier changes

private slots:
  void on_return_pressed();

private:
  int ref;
  double value;
};

#endif // DOUBLE_LINE_EDIT_HH
