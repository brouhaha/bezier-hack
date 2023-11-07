// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <iostream>

#include <QColor>
#include <QPainter>

#include "bezier_graph.hh"

BezierGraph::BezierGraph(BezierObject& bezier,
			 QWidget* parent):
  QGraphicsView(new QGraphicsScene(-135.0, -135.0, 270.0, 270.0, parent), parent),
  bezier(bezier),
  ai(-100.0, 100.0, 20.0),
  bezier_item(bezier),
  cp_bounding_box(2),
  cp_bounding_box_item(QColor(Qt::red)),
  cp_convex_hull_item(QColor("#ffa500"))
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

  update_cp_bounding_box();
  cp_bounding_box_item.setVisible(false);
  scene()->addItem(&cp_bounding_box_item);

  update_cp_convex_hull();
  cp_convex_hull_item.setVisible(false);
  scene()->addItem(&cp_convex_hull_item);

  scene()->addItem(&bezier_item);

  on_bezier_changed();

  connect(&bezier, &BezierObject::value_changed,
	  this,    &BezierGraph::on_bezier_changed);
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

void BezierGraph::on_bezier_changed()  // received when the params values are edited
{
  for (int i = 0; i <= bezier.order(); i++)
  {
    pi[i]->on_position_changed(bezier.get(i, X), 
			       bezier.get(i, Y));
  }
  update_cp_bounding_box();
  update_cp_convex_hull();
}

void BezierGraph::on_point_position_changed(int point_id,
					    double x,
					    double y)
{
  if ((x != bezier.get(point_id, X)) ||
      (y != bezier.get(point_id, Y)))
  {
    bezier.set(point_id, X, x);
    bezier.set(point_id, Y, y);
  }
}

void BezierGraph::on_view_cp_convex_hull_changed([[maybe_unused]] bool visible)
{
  cp_convex_hull_item.setVisible(visible);
}

void BezierGraph::on_view_cp_bounding_box_changed(bool visible)
{
  cp_bounding_box_item.setVisible(visible);
}

void BezierGraph::on_view_bezier_bounding_box_changed([[maybe_unused]] bool visible)
{
}

void BezierGraph::update_cp_bounding_box()
{
  cp_bounding_box = bezier.get_bounding_box();
  cp_bounding_box_item.set_rect(cp_bounding_box);
}

void BezierGraph::update_cp_convex_hull()
{
  std::cout << "update_cp_convex_hull()\n";
  cp_convex_hull_item.set_polygon(bezier.get_control_point_convex_hull());
}
