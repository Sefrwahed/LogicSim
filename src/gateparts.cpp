#include "gateparts.h"

// Qt includes

#include <QtWidgets>

// Local inlcudes

#include "logicsim_global.h"

namespace Logicsim
{

GateBody::GateBody(QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    //setFlag(QGraphicsItem::ItemIsSelectable); //item must be selected first before dragging
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void GateBody::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     Q_UNUSED(event);
}

void GateBody::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
    if(x() - X_MARGIN < 0)
    {
        setPos(X_MARGIN, y());
    }
    else if(x() + boundingRect().right() + X_MARGIN > CANVAS_WIDTH)
    {
        setPos(CANVAS_WIDTH - boundingRect().width() - X_MARGIN, y());
    }

    if(y() < 0)
    {
        setPos(x(), 0);
    }
    else if( y()+ boundingRect().bottom() > CANVAS_HEIGHT)
    {
        setPos(x(), CANVAS_HEIGHT - boundingRect().height());
    }
}

QRectF GateBody::boundingRect() const
{
    return QRectF(0,0,40,50);
}

void GateBody::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawRect(0,0,40,50);
}

// ==============================================

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
