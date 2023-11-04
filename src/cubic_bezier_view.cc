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
    pi[i].set_color(((i == 0) | (i == 3)) ? QColor(Qt::green) : QColor(Qt::blue));
    scene()->addItem(&pi[i]);
  }
  scene()->addItem(&cbi);

  on_cubic_bezier_changed();
}

void CubicBezierView::dump_coordinates()
{
  for (int i = 0; i < 4; i++)
  {
    QRectF r = pi[i].rect();
    std::cout << "p" << i <<": (" << r.x() << ", " << r.y() << "), width " << r.width() << ", hieght " << r.height() << "\n";
    QPointF pos = pi[i].pos();
    std::cout << "p" << i <<" pos: (" << pos.x() << ", " << pos.y() << ")\n";
  }
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
}
