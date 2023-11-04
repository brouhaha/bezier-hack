// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <string>

#include <QLabel>

#include "double_line_edit.hh"
#include "cubic_bezier_params.hh"

CubicBezierParams::CubicBezierParams(CubicBezier& cb,
				     QWidget* parent):
  QWidget(parent),
  cb(cb),
  prev_cb(cb),
  layout(new QGridLayout)
{
  layout->addWidget(new QLabel("x"), 0, 1);
  layout->addWidget(new QLabel("y"), 0, 2);
  for (int i = 0; i < 4; i++)
  {
    char name[3] = { 'p', '0'+i, '\0' };
    layout->addWidget(new QLabel(name), i+1, 0);
    x_coord_le[i] = new DoubleLineEdit(cb.p[i].x, this);
    y_coord_le[i] = new DoubleLineEdit(cb.p[i].y, this);
    layout->addWidget(x_coord_le[i], i+1, 1);
    layout->addWidget(y_coord_le[i], i+1, 2);
    connect(x_coord_le[i], &DoubleLineEdit::value_changed,
	    this,          &CubicBezierParams::on_double_value_changed);
    connect(y_coord_le[i], &DoubleLineEdit::value_changed,
	    this,          &CubicBezierParams::on_double_value_changed);
  }

  setLayout(layout);

  for (int i = 0; i < 4; i++)
  {
    x_coord_le[i]->setText(QString::fromStdString(std::to_string(cb.p[i].x)));
    y_coord_le[i]->setText(QString::fromStdString(std::to_string(cb.p[i].y)));
  }
}

void CubicBezierParams::on_cubic_bezier_changed()
{
  for (int i = 0; i < 4; i++)
  {
    if (cb.p[i].x != prev_cb.p[i].x)
    {
      x_coord_le[i]->setText(QString::fromStdString(std::to_string(cb.p[i].x)));
      prev_cb.p[i].x = cb.p[i].x;
    }
    if (cb.p[i].y != prev_cb.p[i].y)
    {
      y_coord_le[i]->setText(QString::fromStdString(std::to_string(cb.p[i].y)));
      prev_cb.p[i].y = cb.p[i].y;
    }
  }
}

void CubicBezierParams::on_double_value_changed([[maybe_unused]] double value)
{
  emit cubic_bezier_changed();
}
