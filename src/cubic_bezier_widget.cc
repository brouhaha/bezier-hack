// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QHBoxLayout>
#include <QHBoxLayout>

#include "cubic_bezier.hh"
#include "cubic_bezier_graph.hh"
#include "cubic_bezier_params.hh"
#include "cubic_bezier_widget.hh"

CubicBezierWidget::CubicBezierWidget(CubicBezier& cb,
				     QWidget* parent,
				     Qt::WindowFlags f) :
  QWidget(parent, f),
  cb(cb),
  cbp(new CubicBezierParams(cb, this)),
  cbg(new CubicBezierGraph(cb, this)),
  hbox(new QHBoxLayout(this)),
  vbox(new QVBoxLayout())
{
  vbox->addWidget(cbp);
  vbox->addStretch();

  hbox->addWidget(cbg,
		  1);   // stretch - give extra space to the cbg, not the vbox
  hbox->addItem(vbox);

  connect(cbp, &CubicBezierParams::cubic_bezier_changed,
	  cbg, &CubicBezierGraph::on_cubic_bezier_changed);
  connect(cbg, &CubicBezierGraph::cubic_bezier_changed,
	  cbp, &CubicBezierParams::on_cubic_bezier_changed);
}
