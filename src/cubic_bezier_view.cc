// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QPainter>

#include "cubic_bezier_view.hh"

CubicBezierView::CubicBezierView(CubicBezier& cb,
				 QWidget* parent):
  QGraphicsView(new QGraphicsScene(-135.0, -135.0, 270.0, 270.0, parent), parent),
  cb(cb),
  ai(-100.0, 100.0, 20.0),
  cbi(cb)
{
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  scene()->addItem(&ai);
  for (int i = 0; i < pi.size(); i++)
  {
    pi[i].set_point_id(i);
    pi[i].set_color(((i == 0) | (i == 3)) ? QColor(Qt::green) : QColor(Qt::blue));
    connect(&pi[i], &PointItem::position_changed,
	    this,   &CubicBezierView::on_point_position_changed);
    scene()->addItem(&pi[i]);
  }
  scene()->addItem(&cbi);

  on_cubic_bezier_changed();
}

QSize CubicBezierView::sizeHint() const
{
  return QSize(300, 300);
}

void CubicBezierView::zoomToFit()
{
  fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

void CubicBezierView::resizeEvent(QResizeEvent *event)
{
  zoomToFit();
  QGraphicsView::resizeEvent(event);
}

void CubicBezierView::paintEvent(QPaintEvent *event)
{
  static bool first_time = true;
  if (first_time)
  {
    first_time = false;
    zoomToFit();
  }
  QGraphicsView::paintEvent(event);
}

void CubicBezierView::on_cubic_bezier_changed()
{
  for (int i = 0; i < 4; i++)
  {
    pi[i].on_position_changed(cb.p[i].x, 
			      cb.p[i].y);
  }
  cbi.on_cubic_bezier_changed();
}

void CubicBezierView::on_point_position_changed(int point_id,
						double x,
						double y)
{
  if ((x != cb.p[point_id].x) ||
      (y != cb.p[point_id].y))
  {
    cb.p[point_id].x = x;
    cb.p[point_id].y = y;
    cbi.on_cubic_bezier_changed();
    emit cubic_bezier_changed();
  }
}

