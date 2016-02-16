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
        : output(0),
          in1(0),
          in2(0),
          out(0)
    {
    }

    Node*           output;
    qint16          maxInput;
    Component::Type type;
    Pin*            in1;
    Pin*            in2;
    Pin*            out;
    int             metaTypeId;
    QList<Node*>    input;
};

Gate::Gate(Type t)
    : Component(t), d(new Private)
{
    d->output = new Node;
    d->maxInput = 2;

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    d->in1 = new Pin(Pin::Input, this);
    d->in2 = new Pin(Pin::Input, this);
    d->out = new Pin(Pin::Output, this);

    QLineF line(0,0,10,0);
    QGraphicsLineItem *Li1 = new QGraphicsLineItem(line,d->in1);
    QGraphicsLineItem *Li2 = new QGraphicsLineItem(line,d->in2);
    QGraphicsLineItem *Lo1 = new QGraphicsLineItem(line,d->out);

    d->in1->setPos(-20,5);
    d->in2->setPos(-20,35);
    d->out->setPos(50,22.5);
    Li1->setPos(10,5);
    Li2->setPos(10,5);
    Lo1->setPos(-10,5);
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

Node* Gate::outputNode()
{
    return d->output;
}

QList<Node*> Gate::inputList() const
{
    return d->input;
}

void Gate::setInput(QList<Node *> & n)
{
    d->input = n;
}

void Gate::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
    d->in1->updateConnectedLine();
    d->in2->updateConnectedLine();
    d->out->updateConnectedLine();
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
    d->in2->updateConnectedLine();
    d->out->updateConnectedLine();
}

} // namespace Logicsim
