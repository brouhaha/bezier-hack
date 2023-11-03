// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <format>
#include <iostream>
#include <string>

#include <QString>

#include "double_line_edit.hh"

DoubleLineEdit::DoubleLineEdit(double& value,
			       QWidget* parent):
  QLineEdit(parent),
  value(value)
{
  on_value_changed();
  connect(this, &DoubleLineEdit::returnPressed,
	  this, &DoubleLineEdit::on_return_pressed);
}

void DoubleLineEdit::on_value_changed()
{
  setText(QString::fromStdString(std::format("{:g}", value)));
}

void DoubleLineEdit::on_return_pressed()
{
  std::string s = text().toStdString();
  std::cout << "DoubleLineEdit::on_return_pressed() \"" << s << "\"\n";
  double new_value = std::atof(s.c_str());
  std::cout << "DoubleLineEdit::on_return_pressed() " << new_value << "\n";
  if (new_value == value)
    return;
  value = new_value;
  std::cout << "DoubleLineEdit emitting value_changed()\n";
  emit(value_changed(value));
}
