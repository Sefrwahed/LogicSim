#include "gate.h"

// Qt includes

#include <QPainter>

// Local includes

#include "pin.h"
#include "logicsim_global.h"

namespace Logicsim
{

class Gate::Private
{
public:
    Private()
        : in1(0),
          in2(0),
          out(0)
    {
    }

    qint16          maxInput;
    Component::Type type;
    Pin*            in1;
    Pin*            in2;
    Pin*            out;
    int             metaTypeId;
    };

Gate::Gate(Type t)
    : Component(t), d(new Private)
{
    if(t == Gate::NotGate)
    {
        d->maxInput = 1;
    }
    else
    {
        d->maxInput = 2;
    }
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    d->in1 = new Pin(Pin::Input, this);
    d->out = new Pin(Pin::Output, this);

    connect(d->in1, SIGNAL(changed(Pin::Value)),
            this, SLOT(calcOutput()));

    addPins(QList<Pin*>() << d->out << d->in1);
    d->out->setNumber(0);
    d->in1->setNumber(1);

    connect(this, SIGNAL(outputChanged(Pin::Value)),
            d->out, SLOT(updatePinValue(Pin::Value)));

    QLineF line(0,0,10,0);
    QGraphicsLineItem *Li1 = new QGraphicsLineItem(line,d->in1);
    QGraphicsLineItem *Lo1 = new QGraphicsLineItem(line,d->out);

    if(d->maxInput == 1)
    {
        d->in1->setPos(-20,22.5);
        d->out->setPos(50,22.5);
        Li1->setPos(10,5);
        Lo1->setPos(-10,5);
    }
    else
    {
        d->in2 = new Pin(Pin::Input, this);
        d->in2->setNumber(2);
        addPins(QList<Pin*>() << d->in2);

        connect(d->in2, SIGNAL(changed(Pin::Value)),
                this, SLOT(calcOutput()));

        QGraphicsLineItem *Li2 = new QGraphicsLineItem(line,d->in2);
        d->in1->setPos(-20,5);
        d->in2->setPos(-20,35);
        d->out->setPos(50,22.5);
        Li1->setPos(10,5);
        Li2->setPos(10,5);
        Lo1->setPos(-10,5);
    }
}

Pin * Gate::in1()
{
    return d->in1;
}

Pin * Gate::in2()
{
    return d->in2;
}

Gate::~Gate()
{
    delete d;
}

void Gate::setMaxInput(qint16 mi)
{
    d->maxInput = mi;
}

qint16 Gate::maxInput()
{
    return d->maxInput;
}



void Gate::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
    updateConnection();
//    if(x() - GATE_X_MARGIN < 0)
//    {
//        setPos(GATE_X_MARGIN, y());
//    }
//    else if(x() + boundingRect().right() + GATE_X_MARGIN > CANVAS_WIDTH)
//    {
//        setPos(CANVAS_WIDTH - boundingRect().width() - GATE_X_MARGIN, y());
//    }

//    if(y() < 0)
//    {
//        setPos(x(), GATE_Y_MARGIN);
//    }
//    else if( y()+ boundingRect().bottom() + GATE_Y_MARGIN > CANVAS_HEIGHT)
//    {
//        setPos(x(), CANVAS_HEIGHT - boundingRect().height() - GATE_Y_MARGIN);
    //    }
}

void Gate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Component::paint(painter, option, widget);
}

QRectF Gate::boundingRect() const
{
    return QRectF(0,0,40,50);
}

void Gate::updateConnection()
{
    d->in1->updateConnectedLine();
    d->out->updateConnectedLine();
    if(maxInput() > 1)
        d->in2->updateConnectedLine();
}

} // namespace Logicsim
