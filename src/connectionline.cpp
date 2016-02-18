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

    connect(m_out, SIGNAL(changed(bool)),
            m_in, SLOT(updatePinValue(bool)));

    connect(m_out, SIGNAL(changed(bool)),
            this, SLOT(updateColor()));

    m_in->updatePinValue(m_out->value());
}

ConnectionLine::~ConnectionLine()
{
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
        if(m_out->value())
        {
            p.setColor(QColor(0,196,0));
        }
        else
        {
            p.setColor(Qt::red);
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

} // namespace Logicsim
