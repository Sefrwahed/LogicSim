#include "connectionline.h"

#include <QPen>
#include <QPainter>

namespace Logicsim
{

ConnectionLine::ConnectionLine(const QLineF &line,QGraphicsItem* parent)
    : QGraphicsLineItem(line, parent), m_out(0), m_in(0)
{
    setAcceptHoverEvents(true);
//    setToolTip(m_out->toolTip() + " <-> " + m_in->toolTip());
    setFlag(QGraphicsItem::ItemIsSelectable);
}

ConnectionLine::~ConnectionLine()
{
}

Pin *ConnectionLine::output() const
{
    return m_out;
}

Pin *ConnectionLine::input() const
{
    return m_in;
}

void ConnectionLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    QPen p;
    p.setWidthF(2);
    p.setStyle(Qt::DashDotDotLine);
    p.setCapStyle(Qt::RoundCap);
    p.setJoinStyle(Qt::MiterJoin);

    if(isSelected())
    {
        p.setColor(QColor(30,144,255));
        setPen(p);
    }
    else
    {
        p.setColor(Qt::black);
        setPen(p);
    }

    QGraphicsLineItem::paint(painter, option, widget);
}

} // namespace Logicsim
