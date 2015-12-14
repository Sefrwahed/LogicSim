#ifndef GATE_H
#define GATE_H

// Qt includes
#include <QCoreApplication>

// Local includes
#include "node.h"

namespace Logicsim
{

class Gate
{
public:
    enum Type
    {
        AndGate = 0,
        NandGate,
        NorGate,
        NotGate,
        OrGate,
        XnorGate,
        XorGate
    };

public:
    virtual void calcOutput() = 0;
    qint16 maxInput();
    Node* outputNode();
    void setInput(QList<Node*>& n);
    Type type() const;

protected:
    Gate(Type t);
    ~Gate();

    void setMaxInput(qint16 mi);
    QList<Node*> inputList() const;

private:
    QList<Node*> m_input;
    Node*        m_output;
    qint16       m_maxInput;
    Type     m_type;
};

// ===================== AndGate ================

class AndGate: public Gate
{
public:
    AndGate();

    void calcOutput();
};

// ===================== OrGate =================

class OrGate: public Gate
{
public:
    OrGate();

    void calcOutput();
};

// ===================== NotGate ================

class NotGate: public Gate
{
public:
    NotGate();

    void calcOutput();
};

} // namespace Logicsim

#endif // GATE_H
