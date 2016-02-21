#include "connectionline.h"

#include <QPen>
#include <QPainter>

namespace Logicsim
{

ConnectionLine::ConnectionLine(Pin *out, Pin *in, QGraphicsItem* parent)
    : QGraphicsLineItem(parent), m_out(out), m_in(in)
{
    setAcceptHoverEvents(true);
    setToolTip(m_out->parentComponent()->toolTip()
               + " <-> "
               + m_in->parentComponent()->toolTip());

    setLine(QLineF(m_in->centerPos(), m_out->centerPos()));
    setFlag(QGraphicsItem::ItemIsSelectable);

    connect(m_out, SIGNAL(changed(Pin::Value)),
            m_in, SLOT(updatePinValue(Pin::Value)));

    connect(m_out, SIGNAL(changed(Pin::Value)),
            this, SLOT(updateColor()));

    connect(this, SIGNAL(lineDeleted()),
            this, SLOT(disconnectPins()));

    m_in->updatePinValue(m_out->value());
    qDebug() << "Line connected";
}

ConnectionLine::~ConnectionLine()
{
    qDebug() << "Line deleted";
}

Pin *ConnectionLine::output() const
{
    return m_out;
}

void ConnectionLine::setOutputPin(Pin *out)
{
    m_out = out;
}

Pin *ConnectionLine::input() const
{
    return m_in;
}

void ConnectionLine::setInputPin(Pin *in)
{
    m_in = in;
}

void ConnectionLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    QPen p;
    p.setWidthF(2);
    p.setStyle(Qt::DashLine);
    p.setCapStyle(Qt::RoundCap);
    p.setJoinStyle(Qt::MiterJoin);

    if(isSelected())
    {
        p.setColor(QColor(30,144,255));
    }
    else
    {
        if(m_out->value() == Pin::True)
        {
            p.setColor(QColor(0,196,0));
        }
        else if(m_out->value() == Pin::False)
        {
            p.setColor(Qt::red);
        }
        else
        {
            p.setColor(Qt::gray);
        }
    }
    setPen(p);

    QGraphicsLineItem::paint(painter, option, widget);
}

void ConnectionLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    qDebug() << "Line pressed bayn kedda";

    emit lineSelected();
}

void ConnectionLine::updateColor()
{
    update();
}

void ConnectionLine::disconnectPins()
{
    disconnect(m_out, SIGNAL(changed(Pin::Value)),
            m_in, SLOT(updatePinValue(Pin::Value)));

    disconnect(m_out, SIGNAL(changed(Pin::Value)),
            this, SLOT(updateColor()));
}

} // namespace Logicsim
