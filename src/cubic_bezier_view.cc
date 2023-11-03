// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QPainter>

#include "axes_item.hh"
#include "cubic_bezier.hh"
#include "cubic_bezier_item.hh"
#include "cubic_bezier_point_item.hh"
#include "cubic_bezier_view.hh"

CubicBezierView::CubicBezierView(CubicBezier& cb,
				 QWidget* parent):
  QGraphicsView(new QGraphicsScene(-135.0, -135.0, 270.0, 270.0, parent), parent),
  cb(cb),
  //cbi(new CubicBezierItem(cb),
  ai(new AxesItem(-100.0, 100.0, 20.0))
{
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  scene()->addItem(ai);
  //scene()->addItem(cbi);

  for (int i = 0; i < 4; i++)
  {
    pi[i] = new CubicBezierPointItem((i == 0) || (i == 3), ai);
    scene()->addItem(pi[i]);
  }
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
    pi[i]->on_position_changed(cb.p[i].x, 
			       cb.p[i].y);
  }
}
