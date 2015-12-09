#include "graphicgate.h"

// Local includes

#include "gateparts.h"
#include "abstractgate.h"

namespace Logicsim
{

GraphicGate::GraphicGate(AbstractGate::Type t, QGraphicsItem *parent)
    : QGraphicsObject(parent), AbstractGate(t)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    QGraphicsObject *in1 = new Input(this);
    QGraphicsObject *in2 = new Input(this);
    QGraphicsObject *out1 = new Output(this);

    QGraphicsObject *Li1 = new ConnectingLine(in1);
    QGraphicsObject *Li2 = new ConnectingLine(in2);
    QGraphicsObject *Lo1 = new ConnectingLine(out1);

    in1->setPos(-15,15);
    in2->setPos(-15,35);
    out1->setPos(50,25);
    Li1->setPos(5,2.5);
    Li2->setPos(5,2.5);
    Lo1->setPos(-10,2.5);
}

QRectF GraphicGate::boundingRect() const
{
    return QRectF(0,0,40,50);
}

void GraphicGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

} // namespace Logicsim
