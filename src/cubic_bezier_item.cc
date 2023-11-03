// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QPainter>

#include "cubic_bezier_item.hh"
#include "cubic_bezier_view.hh"

CubicBezierView::CubicBezierView(CubicBezier& cb,
				 QWidget* parent):
  QGraphicsView(new QGraphicsScene, parent),
  cb(cb),
  cbi(new CubicBezierItem(cb)
{
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  scene()->addItem(cbi);
}

QSize CubicBezierView::sizeHint() const
{
  return QSize(400, 400);
}

void CubicBezierView::zoomToFit()
{
  fitInView(scene()->scenRect(), Qt::KeepAspectRatio);
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



