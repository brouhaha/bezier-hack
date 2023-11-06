// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QPainter>

#include "bezier_graph.hh"

BezierGraph::BezierGraph(Bezier& bezier,
			 QWidget* parent):
  QGraphicsView(new QGraphicsScene(-135.0, -135.0, 270.0, 270.0, parent), parent),
  bezier(bezier),
  ai(-100.0, 100.0, 20.0),
  bezier_item(bezier)
{
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  scene()->addItem(&ai);
  for (int i = 0; i <= bezier.order(); i++)
  {
    pi.push_back(std::make_unique<PointItem>(i));
    pi[i]->set_point_id(i);
    pi[i]->set_color(((i == 0) | (i == bezier.order())) ? QColor(Qt::green) : QColor(Qt::blue));
    connect(pi[i].get(), &PointItem::position_changed,
	    this,        &BezierGraph::on_point_position_changed);
    scene()->addItem(pi[i].get());
  }
  scene()->addItem(&bezier_item);

  on_bezier_changed();
}

QSize BezierGraph::sizeHint() const
{
  return QSize(300, 300);
}

void BezierGraph::zoomToFit()
{
  fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

void BezierGraph::resizeEvent(QResizeEvent *event)
{
  zoomToFit();
  QGraphicsView::resizeEvent(event);
}

void BezierGraph::paintEvent(QPaintEvent *event)
{
  static bool first_time = true;
  if (first_time)
  {
    first_time = false;
    zoomToFit();
  }
  QGraphicsView::paintEvent(event);
}

void BezierGraph::on_bezier_changed()
{
  for (int i = 0; i <= bezier.order(); i++)
  {
    pi[i]->on_position_changed(bezier[i][X], 
			       bezier[i][Y]);
  }
  bezier_item.on_bezier_changed();
}

void BezierGraph::on_point_position_changed(int point_id,
					    double x,
					    double y)
{
  if ((x != bezier[point_id][X]) ||
      (y != bezier[point_id][Y]))
  {
    bezier[point_id][X] = x;
    bezier[point_id][Y] = y;
    bezier_item.on_bezier_changed();
    emit bezier_changed();
  }
}

