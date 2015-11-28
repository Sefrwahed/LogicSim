#include "node.h"
namespace Logicsim
{
Node::Node()
{
    value = 0;
    name = "n";
}
QString Node::getName()
{
    return name;
}
bool Node::getValue()
{
    return value;
}
void Node::setValue(bool v)
{
    value = v;
}
void Node::setName(QString n)
{
    name = n;
}

} //namespace Logicsim
