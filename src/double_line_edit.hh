// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef DOUBLE_LINE_EDIT_HH
#define DOUBLE_LINE_EDIT_HH

#include <QLineEdit>

class DoubleLineEdit: public QLineEdit
{
  Q_OBJECT

public:
  DoubleLineEdit(double& value,
		 QWidget* parent = nullptr);

public slots:
  void on_value_changed();  // received when user drags handles

signals:
  void value_changed(double value);  // emitted when user edits a numeric value

private slots:
  void on_return_pressed();

private:
  double& value;
};

#endif // DOUBLE_LINE_EDIT_HH
