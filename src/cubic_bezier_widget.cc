// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QHBoxLayout>
#include <QHBoxLayout>

#include "bezier.hh"
#include "cubic_bezier_graph.hh"
#include "cubic_bezier_params.hh"
#include "cubic_bezier_widget.hh"

CubicBezierWidget::CubicBezierWidget(Bezier& bezier,
				     QWidget* parent,
				     Qt::WindowFlags f) :
  QWidget(parent, f),
  bezier(bezier),
  cbp(new CubicBezierParams(bezier, this)),
  cbg(new CubicBezierGraph(bezier, this)),
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

void CubicBezierWidget::on_view_graph_changed(bool visible)
{
  std::cout << "CubicBezierWidget::on_view_graph_changed(" << visible << ")\n";
  cbg->setVisible(visible);
}

void CubicBezierWidget::on_view_params_changed(bool visible)
{
  std::cout << "CubicBezierWidget::on_view_parameters_changed(" << visible << ")\n";
  cbp->setVisible(visible);
}
