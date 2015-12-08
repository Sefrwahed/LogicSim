#include "node.h"

namespace Logicsim
{

Node::Node()
{
    m_value = 0;
    m_name = "n";
}

QString Node::name()
{
    return m_name;
}

bool Node::value()
{
    return m_value;
}

void Node::setValue(bool v)
{
    m_value = v;
}

void Node::setName(QString n)
{
    m_name = n;
}

} //namespace Logicsim
