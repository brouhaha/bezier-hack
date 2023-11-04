// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef CUBIC_BEZIER_VIEW_HH
#define CUBIC_BEZIER_VIEW_HH

#include <QGraphicsView>

#include "cubic_bezier.hh"
#include "axes_item.hh"
#include "point_item.hh"
#include "cubic_bezier_item.hh"

class CubicBezierView: public QGraphicsView
{
  Q_OBJECT

public:
  CubicBezierView(CubicBezier& cb,
		  QWidget* parent = nullptr);

  void zoomToFit();

  QSize sizeHint() const override;

signals:
  void cubic_bezier_changed();  // emitted when user drags handles

public slots:
  void on_cubic_bezier_changed();  // received when the params values are edited

private slots:
  void on_point_position_changed(int point_id,
				 double x,
				 double y);

protected:
  void resizeEvent(QResizeEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

private:
  CubicBezier& cb;
  AxesItem ai;
  std::array<PointItem, 4> pi;
  CubicBezierItem cbi;
};

#endif // CUBIC_BEZIER_VIEW_HH
