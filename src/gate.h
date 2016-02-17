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
    ~Gate();

    qint16 maxInput();
    Node* outputNode();
    void setInput(QList<Node*>& n);
    QList<Node*> inputList() const;

//    virtual void calcOutput() = 0;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const;
    void updateConnection();

protected:
    Gate(Type t);

    void setMaxInput(qint16 mi);
public Q_SLOTS:
    virtual void calcOutput()=0;

private:
    class Private;
    Private* const d;
};

}
#endif // GATE_H
