#include <QCoreApplication>
#include "node.h"
#ifndef GATE_H
#define GATE_H
namespace Logicsim {

class Gate
{
    QList<Node*> input;
    Node* output;

public:
    virtual void calcOutput() = 0;


};
}
#endif // GATE_H
