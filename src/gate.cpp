#include "gate.h"

namespace Logicsim
{

Gate::Gate(Type t)
{
    m_type = t;
    m_output = new Node;
    m_maxInput = 2;
}

Gate::~Gate()
{
    delete m_output;
}

void Gate::setMaxInput(qint16 mi)
{
    m_maxInput = mi;
}

qint16 Gate::maxInput(){
    return m_maxInput;
}

Node* Gate::outputNode()
{
    return m_output;
}

QList<Node*> Gate::inputList() const
{
    return m_input;
}

void Gate::setInput(QList<Node *> & n)
{
    m_input = n;
}

Gate::Type Gate::type() const
{
    return m_type;
}

// ===================== AndGate ===================

AndGate::AndGate()
    : Gate(Gate::AndGate)
{
}

void AndGate::calcOutput()
{
    bool out = true;
    foreach (Node * n, inputList()) {
        out &= n->value();
    }

    outputNode()->setValue(out);
}

// ===================== OrGate ===================

OrGate::OrGate()
    : Gate(Gate::OrGate)
{
}

void OrGate::calcOutput()
{
    bool out = false;
    foreach (Node * n, inputList()) {
        out |= n->value();
    }

    outputNode()->setValue(out);

}

// ===================== NotGate ===================

NotGate::NotGate()
    : Gate(Gate::NotGate)
{
    setMaxInput(1);
}

void NotGate::calcOutput()
{
    bool out = inputList()[0]->value();
    outputNode()->setValue(!out);
}

} // namespace Logicsim
