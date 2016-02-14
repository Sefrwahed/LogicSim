#include "pin.h"

// Qt includes

#include <QtWidgets>

// Local inlcudes

#include "logicsim_global.h"

namespace Logicsim
{

Pin::Pin(Type t, Component *parent)
    : QGraphicsObject(parent), m_line(0)
{
    m_type = t;
    m_parent = parent;
}

Pin::~Pin()
{
}

bool Pin::isConnected()
{
    return m_line != 0;
}

void Pin::setConnected(ConnectionLine *line)
{
    m_line = line;
}

void Pin::updateConnectedLine()
{
    if(isConnected())
    {
        qDebug() << "It's connected";
        if(m_type == Input)
        {
            QLineF oldLine = m_line->line();
            m_line->setLine(QLineF(centerPos(), oldLine.p2()));
        }
        else
        {
            QLineF oldLine = m_line->line();
            m_line->setLine(QLineF(oldLine.p1(), centerPos()));
        }
    }
}

QPointF Pin::centerPos() const
{
    return QPointF(scenePos().x() + boundingRect().width()/2,
                   scenePos().y() + boundingRect().height()/2);
}

int Pin::type() const
{
    return m_type;
}

Component *Pin::parentComponent() const
{
    return m_parent;
}

QRectF Pin::boundingRect() const
{
    return QRectF(0,0,10,10);
}

void Pin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawEllipse(boundingRect());
}

void Pin::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"Output Clicked";
}

void Pin::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Pin is moooooving !!";
    updateConnectedLine();
}

} // namespace Logicsim
