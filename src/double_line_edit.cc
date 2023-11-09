// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <string>

#include <QDoubleValidator>
#include <QString>

#include "double_line_edit.hh"

DoubleLineEdit::DoubleLineEdit(int ref,
			       double value,
			       QWidget* parent):
  QLineEdit(parent),
  ref(ref),
  value(value)
{
  setValidator(new QDoubleValidator(-100.0, 100.0, -1, this));
  on_value_changed(value);
  connect(this, &DoubleLineEdit::editingFinished,
	  this, &DoubleLineEdit::on_return_pressed);
}

void DoubleLineEdit::on_value_changed(double value)
{
  setText(QString::fromStdString(std::to_string(value)));
}

void DoubleLineEdit::on_return_pressed()
{
  std::string s = text().toStdString();
  double new_value = std::atof(s.c_str());
  if (new_value == value)
    return;
  value = new_value;
  emit(value_changed(ref, value));
}
