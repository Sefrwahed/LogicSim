#include "node.h"

namespace Logicsim
{

Node::Node()
{
    m_value = 0;
    m_name = "n";
    calc = 0;
}

Node::Node(bool c)
{
    m_value = 0;
    m_name = "n";
    calc = c;
}

QString Node::name()
{
    return m_name;
}

bool Node::value()
{
    return m_value;
}

bool Node::isCalc()
{
    return calc;
}

void Node::setValue(bool v)
{
    m_value = v;
}

void Node::setCalc(bool c)
{
    calc = c;
}

void Node::setName(QString n)
{
    m_name = n;
}

} //namespace Logicsim
