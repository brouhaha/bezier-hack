// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QHBoxLayout>
#include <QHBoxLayout>

#include "bezier.hh"
#include "bezier_graph.hh"
#include "bezier_params.hh"
#include "bezier_widget.hh"

BezierWidget::BezierWidget(Bezier& bezier,
			   QWidget* parent,
			   Qt::WindowFlags f) :
  QWidget(parent, f),
  bezier(bezier),
  bezier_params(new BezierParams(bezier, this)),
  bezier_graph(new BezierGraph(bezier, this)),
  hbox(new QHBoxLayout(this)),
  vbox(new QVBoxLayout())
{
  vbox->addWidget(bezier_params);
  vbox->addStretch();

  hbox->addWidget(bezier_graph,
		  1);   // stretch - give extra space to the cbg, not the vbox
  hbox->addItem(vbox);

  connect(bezier_params, &BezierParams::bezier_changed,
	  bezier_graph,  &BezierGraph::on_bezier_changed);
  connect(bezier_graph,  &BezierGraph::bezier_changed,
	  bezier_params, &BezierParams::on_bezier_changed);
}

void BezierWidget::on_view_graph_changed(bool visible)
{
  bezier_graph->setVisible(visible);
}

void BezierWidget::on_view_params_changed(bool visible)
{
  bezier_params->setVisible(visible);
}
