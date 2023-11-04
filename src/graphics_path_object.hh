// Copyright (C) 2021 The Qt Company Ltd.
// Copyright 2023 Eric Smith
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

// This file is largely based on the Qt6 source file
// src/widgets/graphicsview/qgraphicsitem.cpp

#ifndef GRAPHICS_PATH_OBJECT_HH
#define GRAPHICS_PATH_OBJECT_HH

#include <memory>

#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QPointF>
#include <QRectF>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class GraphicsPathObjectPrivate;

class GraphicsPathObject: public QGraphicsObject
{
public:
  GraphicsPathObject(const QPainterPath &path,
		     QGraphicsItem *parent);
  GraphicsPathObject(QGraphicsItem *parent);

  ~GraphicsPathObject();

  int type() const;

  QPen pen() const;
  void setPen(const QPen& pen);
  QBrush brush() const;
  void setBrush(const QBrush& brush);
  QPainterPath path() const;
  void setPath(const QPainterPath& path);

  QRectF boundingRect() const override;
  QPainterPath shape() const override;

  // XXX from QAbstractGraphicsShape?
  //bool contains(const QPointF& ) const override;
  //bool isObscuredBy(const QGraphicsItem* item) const override;
  QPainterPath opaqueArea() const override;
  
  void paint(QPainter* painter,
	     const QStyleOptionGraphicsItem* option,
	     QWidget* widget);

private:
  static constexpr int custom_type = QGraphicsItem::UserType + 1;

  QBrush m_brush;
  QPen m_pen;
  QPainterPath m_path;
  std::unique_ptr<GraphicsPathObjectPrivate> d_ptr;

  void highlight_selected(QPainter *painter,
			  const QStyleOptionGraphicsItem *option);

  static QPainterPath shape_from_path(const QPainterPath& path,
				      const QPen& pen);

};

#endif // GRAPHICS_PATH_OBJECT_HH
