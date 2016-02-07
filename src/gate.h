#ifndef GATE_H
#define GATE_H

// Local includes

#include "component.h"
#include "node.h"

namespace Logicsim
{

class Gate : public Component
{
public:
//    enum Type
//    {
//        AndGate = 0,
//        OrGate,
//        NotGate,
//        NandGate,
//        NorGate,
//        XorGate,
//        XnorGate
//    };

public:
    ~Gate();

    qint16 maxInput();
    Node* outputNode();
    void setInput(QList<Node*>& n);
    Type gateType() const;

    virtual void calcOutput() = 0;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    QRectF boundingRect() const;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    Gate(Type t);

    void setMaxInput(qint16 mi);
    QList<Node*> inputList() const;

private:
    class Private;
    Private* const d;
};

}
#endif // GATE_H
