#include "connectionline.h"

#include <QPen>
#include <QPainter>

namespace Logicsim
{

ConnectionLine::ConnectionLine(const QLineF &line,QGraphicsItem* parent)
    : QGraphicsLineItem(line, parent), m_out(0), m_in(0)
{
    QPen p;
    p.setWidthF(2);
    setPen(p);
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
    QGraphicsLineItem::paint(painter, option, widget);
}

} // namespace Logicsim
