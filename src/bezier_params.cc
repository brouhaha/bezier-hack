// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <format>
#include <string>

#include <QLabel>

#include "double_line_edit.hh"
#include "bezier_params.hh"

BezierParams::BezierParams(BezierObject& bezier,
			   QWidget* parent):
  QWidget(parent),
  bezier(bezier),
  layout(new QGridLayout)
{
  layout->addWidget(new QLabel("x"), 0, 1);
  layout->addWidget(new QLabel("y"), 0, 2);
  for (int i = 0; i <= bezier.order(); i++)
  {
    layout->addWidget(new QLabel(QString::fromStdString(std::format("p{}", i+1))));
    x_coord_le[i] = new DoubleLineEdit(2*i,   0.0, this);
    y_coord_le[i] = new DoubleLineEdit(2*i+1, 0.0, this);
    layout->addWidget(x_coord_le[i], i+1, 1);
    layout->addWidget(y_coord_le[i], i+1, 2);
    connect(x_coord_le[i], &DoubleLineEdit::value_changed,
	    this,          &BezierParams::on_double_value_changed);
    connect(y_coord_le[i], &DoubleLineEdit::value_changed,
	    this,          &BezierParams::on_double_value_changed);
  }

  connect(&bezier, &BezierObject::value_changed,
	  this,    &BezierParams::on_bezier_changed);

  on_bezier_changed();

  setLayout(layout);
}


void BezierParams::on_bezier_changed()
{
  for (int i = 0; i <= bezier.order(); i++)
  {
    x_coord_le[i]->setText(QString::fromStdString(std::to_string(bezier.get(i, X))));
    y_coord_le[i]->setText(QString::fromStdString(std::to_string(bezier.get(i, Y))));
  }
}

void BezierParams::on_double_value_changed(int ref, double value)
{
  bezier.set(ref/2, ref%2, value);
}
