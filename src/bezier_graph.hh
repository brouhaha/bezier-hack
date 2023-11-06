// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef BEZIER_GRAPH_HH
#define BEZIER_GRAPH_HH

#include <memory>

#include <QGraphicsView>

#include "bezier.hh"
#include "axes_item.hh"
#include "point_item.hh"
#include "bezier_item.hh"

class BezierGraph: public QGraphicsView
{
  Q_OBJECT

public:
  BezierGraph(Bezier& bezier,
	      QWidget* parent = nullptr);

  void zoomToFit();

  QSize sizeHint() const override;

signals:
  void bezier_changed();  // emitted when user drags handles

public slots:
  void on_bezier_changed();  // received when the params values are edited

private slots:
  void on_point_position_changed(int point_id,
				 double x,
				 double y);

protected:
  void resizeEvent(QResizeEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

private:
  Bezier& bezier;
  AxesItem ai;
  std::vector<std::unique_ptr<PointItem>> pi;
  BezierItem bezier_item;
};

#endif // BEZIER_GRAPH_HH
