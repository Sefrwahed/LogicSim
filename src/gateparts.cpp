#include "gateparts.h"

// Qt includes

#include <QtWidgets>

// Local inlcudes

#include "logicsim_global.h"

namespace Logicsim
{

Input::Input(QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
}

void Input::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"Input Clicked";
}

QRectF Input::boundingRect() const
{
    return QRectF(0,0,5,5);
}

void Input::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(Qt::SolidPattern);
    painter->drawEllipse(0,0,5,5);
}

// ==============================================

Output::Output(QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
}

void Output::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"Output Clicked";
}

QRectF Output::boundingRect() const
{
    return QRectF(0,0,5,5);
}

void Output::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(Qt::SolidPattern);
    painter->drawEllipse(0,0,5,5);
}

// ==============================================

ConnectingLine::ConnectingLine(QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
}

QRectF ConnectingLine::boundingRect() const
{
    return QRectF(0,0,10,0);
}

void ConnectingLine::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawLine(0,0,10,0);
}

} // namespace Logicsim
