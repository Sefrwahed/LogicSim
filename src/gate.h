#ifndef GATE_H
#define GATE_H

// Local includes

#include "component.h"
#include "pin.h"

namespace Logicsim
{

class Gate : public Component
{
    Q_OBJECT
public:
    ~Gate();

    qint16 maxInput();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const;
    void updateConnection();

protected:
    Gate(Type t);
    Pin * in1();
    Pin * in2();

    void setMaxInput(qint16 mi);
public Q_SLOTS:
    virtual void calcOutput()=0;
Q_SIGNALS:
    void outputChanged(Pin::Value value);

private:
    class Private;
    Private* const d;
};

}
#endif // GATE_H
