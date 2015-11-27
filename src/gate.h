#ifndef GATE_H
#define GATE_H

#include <QCoreApplication>
#include "node.h"

namespace Logicsim
{

class Gate
{
public:
    Gate();
    ~Gate();
    virtual void calcOutput() = 0;
    void setMaxInput(qint16 mi);
    qint16 getMaxInput();
    void setInput(QList<Node*>& n);
    Node* outputNode();

protected:

    QList<Node*> inputList() const;

private:
    QList<Node*> input;
    Node* output;
    qint16 maxInput;
};
// ===================== AndGate ===================
class AndGate: public Gate
 {
 public:
    void calcOutput();

};

// ===================== OrGate ===================
class OrGate: public Gate
 {
 public:
    void calcOutput();

};

// ===================== NotGate ===================
class NotGate: public Gate
 {
 public:
    NotGate();
    void calcOutput();

};



}
#endif // GATE_H
