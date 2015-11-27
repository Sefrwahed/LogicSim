#include "gate.h"

namespace Logicsim
{

Gate::Gate()
{
    output = new Node;
    maxInput = 2;
}

Gate::~Gate()
{
    delete output;
}

void Gate::setMaxInput(qint16 mi)
{
    maxInput = mi;
}

qint16 Gate::getMaxInput(){
    return maxInput;
}

Node* Gate::outputNode()
{
    return output;
}

QList<Node*> Gate::inputList() const
{
    return input;
}

void Gate::setInput(QList<Node *> &n)
{
    input = n;
}

// ===================== AndGate ===================

void AndGate::calcOutput()
{
    bool out = true;
    foreach (Node * n, inputList()) {
        out &= n->getValue();
    }

    outputNode()->setValue(out);
}

// ===================== OrGate ===================

void OrGate::calcOutput()
{
    bool out = false;
    foreach (Node * n, inputList()) {
        out |= n->getValue();
    }

    outputNode()->setValue(out);

}
// ===================== NotGate ===================
NotGate::NotGate()
{
    setMaxInput(1);
}

void NotGate::calcOutput()
{
    bool out = inputList()[0]->getValue();
    outputNode()->setValue(!out);
}

} // namespace Logicsim
