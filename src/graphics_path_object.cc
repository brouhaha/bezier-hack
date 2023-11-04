// Copyright (C) 2021 The Qt Company Ltd.
// Copyright 2023 Eric Smith
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

// This file is largely based on the Qt6 source file
// src/widgets/graphicsview/qgraphicsitem.cpp

#include "graphics_path_object.hh"


class GraphicsPathObjectPrivate
{
  QRectF bounding_rect;

  friend class GraphicsPathObject;
};


GraphicsPathObject::GraphicsPathObject(const QPainterPath & path,
				       QGraphicsItem *parent):
  QGraphicsObject(parent),
  d_ptr(std::make_unique<GraphicsPathObjectPrivate>())
{
  if (! path.isEmpty())
  {
    setPath(path);
  }
}

GraphicsPathObject::GraphicsPathObject(QGraphicsItem *parent):
  QGraphicsObject(parent),
  d_ptr(std::make_unique<GraphicsPathObjectPrivate>())
{
}

GraphicsPathObject::~GraphicsPathObject()
{
}

int GraphicsPathObject::type() const
{
  return custom_type;
}

QPen GraphicsPathObject::pen() const
{
  return m_pen;
}

void GraphicsPathObject::setPen(const QPen& pen)
{
  m_pen = pen;
}

QBrush GraphicsPathObject::brush() const
{
  return m_brush;
}

void GraphicsPathObject::setBrush(const QBrush& brush)
{
  m_brush = brush;
}

QPainterPath GraphicsPathObject::path() const
{
  return m_path;
}

void GraphicsPathObject::setPath(const QPainterPath& path)
{
  if (path == m_path)
    return;
  prepareGeometryChange();
  m_path = path;
  d_ptr->bounding_rect = QRectF();
  update();
}

QRectF GraphicsPathObject::boundingRect() const
{
  if (d_ptr->bounding_rect.isNull())
  {
    qreal pw = m_pen.style() == Qt::NoPen ? 0.0 : m_pen.widthF();
    if (pw == 0.0)
    {
      d_ptr->bounding_rect = m_path.controlPointRect();
    }
    else
    {
      d_ptr->bounding_rect = shape().controlPointRect();
    }
  }
    
  return d_ptr->bounding_rect;
}

QPainterPath GraphicsPathObject::shape() const
{
  return shape_from_path(m_path, m_pen);
}

#if 0
bool GraphicsPathObject::contains(const QPointF& ) const
{
}

bool GraphicsPathObject::isObscuredBy(const QGraphicsItem* item) const
{
}
#endif

QPainterPath GraphicsPathObject::opaqueArea() const
{
  if (m_brush.isOpaque())
    return isClipped() ? clipPath() : shape();
  return QGraphicsItem::opaqueArea();
}

void GraphicsPathObject::paint(QPainter* painter,
			       const QStyleOptionGraphicsItem* option,
			       [[maybe_unused]] QWidget* widget)
{
  painter->setPen(m_pen);
  painter->setBrush(m_brush);
  painter->drawPath(m_path);
  if (option->state & QStyle::State_Selected)
  {
    highlight_selected(painter, option);
  }
}


void GraphicsPathObject::highlight_selected(QPainter *painter,
					    const QStyleOptionGraphicsItem *option)
{
  const QRectF murect = painter->transform().mapRect(QRectF(0, 0, 1, 1));
  if (qFuzzyIsNull(qMax(murect.width(), murect.height())))
  {
    return;
  }

  const QRectF mbrect = painter->transform().mapRect(boundingRect());
  if (qMin(mbrect.width(), mbrect.height()) < qreal(1.0))
  {
    return;
  }

  qreal pad = m_pen.widthF() / 2;

  const QColor fgcolor = option->palette.windowText().color();
  const QColor bgcolor(fgcolor.red()   > 127 ? 0 : 255,
		       fgcolor.green() > 127 ? 0 : 255,
		       fgcolor.blue()  > 127 ? 0 : 255);

  painter->setBrush(Qt::NoBrush);

  painter->setPen(QPen(bgcolor, 0, Qt::SolidLine));
  painter->drawRect(boundingRect().adjusted(pad, pad, -pad, -pad));

  painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));
  painter->drawRect(boundingRect().adjusted(pad, pad, -pad, -pad));
}

QPainterPath GraphicsPathObject::shape_from_path(const QPainterPath& path,
						 const QPen& pen)
{
  const qreal penWidthZero = qreal(0.00000001);

  if (path == QPainterPath() || pen == Qt::NoPen)
    return path;
  QPainterPathStroker ps;
  ps.setCapStyle(pen.capStyle());
  if (pen.widthF() <= 0.0)
    ps.setWidth(penWidthZero);
  else
    ps.setWidth(pen.widthF());
  ps.setJoinStyle(pen.joinStyle());
  ps.setMiterLimit(pen.miterLimit());
  QPainterPath p = ps.createStroke(path);
  p.addPath(path);
  return p;
}
