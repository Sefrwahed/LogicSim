#include "pin.h"

// Qt includes

#include <QtWidgets>

// Local inlcudes

#include "logicsim_global.h"

namespace Logicsim
{

Pin::Pin(Type t, Component *parent)
    : QGraphicsObject(parent), m_number(0)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    m_type = t;
    m_parent = parent;
    m_value = Pin::Undefined;
}

Pin::~Pin()
{
}

bool Pin::isConnected()
{
    return m_lines.length() != 0;
}

void Pin::setConnected(ConnectionLine *line)
{
    if(m_type == Output)
    {
        m_lines << line;

    }
    else if( m_lines.length() == 0)
    {
        m_lines << line;
    }
    else
    {
        return;
    }

    connect(line, SIGNAL(lineDeleted()),
            this, SLOT(disconnectLine()));
}

void Pin::setNumber(quint32 n)
{
    m_number = n;
}

quint32 Pin::number() const
{
    return m_number;
}

void Pin::updateConnectedLine()
{
    if(isConnected())
    {
        if(m_type == Input)
        {
            QLineF oldLine = m_lines[0]->line();
            m_lines.at(0)->setLine(QLineF(centerPos(), oldLine.p2()));
        }
        else
        {
            foreach(ConnectionLine* l, m_lines)
            {
                QLineF oldLine = l->line();
                l->setLine(QLineF(oldLine.p1(), centerPos()));
                l->update();
            }
        }
    }
}

QList<ConnectionLine *> &Pin::connectedLines()
{
    return m_lines;
}

Pin::Value Pin::value()
{
    return m_value;
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
    QPen p;
    p.setWidthF(2);
    painter->setPen(p);
    painter->setRenderHint(painter->Antialiasing);
    if(isSelected())
    {
        p.setColor(QColor(30,144,255));
        painter->setPen(p);
    }
    else
    {
        p.setColor(Qt::black);
        painter->setPen(p);
    }
    painter->drawEllipse(boundingRect());
}

void Pin::disconnectLine()
{
    qDebug() << "PIN LINE DISCONNECT";
    m_lines.removeOne(static_cast<ConnectionLine*>(sender()));
    if(m_type == Pin::Input)
        updatePinValue(Pin::Undefined);
}

void Pin::updatePinValue(Pin::Value value)
{
    m_value = value;
    m_parent->update();
    emit changed(value);
}

void Pin::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void Pin::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Pin is moooooving !!";
    updateConnectedLine();
}

} // namespace Logicsim
