#include "connectionline.h"

namespace Logicsim
{

ConnectionLine::ConnectionLine(const QLineF &line,QGraphicsItem* parent)
    : QGraphicsLineItem(line, parent), m_out(0), m_in(0)
{
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

} // namespace Logicsim
