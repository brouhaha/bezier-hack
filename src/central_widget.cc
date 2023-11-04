// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QHBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>

#include "cubic_bezier.hh"
#include "cubic_bezier_params.hh"
#include "cubic_bezier_view.hh"
#include "central_widget.hh"

CentralWidget::CentralWidget(CubicBezier& cb,
			     QWidget* parent,
			     Qt::WindowFlags f) :
  QWidget(parent, f),
  cb(cb),
  cbp(new CubicBezierParams(cb, this)),
  cbv(new CubicBezierView(cb, this)),
  hbox(new QHBoxLayout(this)),
  vbox(new QVBoxLayout(this))
{
  vbox->addWidget(cbp);
  vbox->addStretch();

  hbox->addWidget(cbv,
		  1);   // stretch - give extra space to the cbv, not the vbox
  hbox->addItem(vbox);

  setLayout(hbox);

  connect(cbp, &CubicBezierParams::cubic_bezier_changed,
	  cbv, &CubicBezierView::on_cubic_bezier_changed);
  connect(cbv, &CubicBezierView::cubic_bezier_changed,
	  cbp, &CubicBezierParams::on_cubic_bezier_changed);
}
