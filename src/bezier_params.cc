// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <format>
#include <string>

#include <QLabel>

#include "double_line_edit.hh"
#include "bezier_params.hh"

BezierParams::BezierParams(Bezier& bezier,
			   QWidget* parent):
  QWidget(parent),
  bezier(bezier),
  prev_bezier(bezier),
  layout(new QGridLayout)
{
  layout->addWidget(new QLabel("x"), 0, 1);
  layout->addWidget(new QLabel("y"), 0, 2);
  for (int i = 0; i <= bezier.order(); i++)
  {
    layout->addWidget(new QLabel(QString::fromStdString(std::format("p{}", i+1))));
    x_coord_le[i] = new DoubleLineEdit(bezier[i][X], this);
    y_coord_le[i] = new DoubleLineEdit(bezier[i][Y], this);
    layout->addWidget(x_coord_le[i], i+1, 1);
    layout->addWidget(y_coord_le[i], i+1, 2);
    connect(x_coord_le[i], &DoubleLineEdit::value_changed,
	    this,          &BezierParams::on_double_value_changed);
    connect(y_coord_le[i], &DoubleLineEdit::value_changed,
	    this,          &BezierParams::on_double_value_changed);
  }

  setLayout(layout);

  for (int i = 0; i <= bezier.order(); i++)
  {
    x_coord_le[i]->setText(QString::fromStdString(std::to_string(bezier[i][X])));
    y_coord_le[i]->setText(QString::fromStdString(std::to_string(bezier[i][Y])));
  }
}

void BezierParams::on_bezier_changed()
{
  for (int i = 0; i <= bezier.order(); i++)
  {
    if (bezier[i][X] != prev_bezier[i][X])
    {
      x_coord_le[i]->setText(QString::fromStdString(std::to_string(bezier[i][X])));
      prev_bezier[i][X] = bezier[i][X];
    }
    if (bezier[i][Y] != prev_bezier[i][Y])
    {
      y_coord_le[i]->setText(QString::fromStdString(std::to_string(bezier[i][Y])));
      prev_bezier[i][Y] = bezier[i][Y];
    }
  }
}

void BezierParams::on_double_value_changed([[maybe_unused]] double value)
{
  emit bezier_changed();
}
