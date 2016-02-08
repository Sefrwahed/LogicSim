#include "gate.h"

// Local includes

#include "gateparts.h"
#include "logicsim_global.h"

namespace Logicsim
{

class Gate::Private
{
public:
    Private()
    {
    }

    QList<Node*> input;
    Node*        output;
    qint16       maxInput;
    Component::Type   type;
    int          metaTypeId;
};

Gate::Gate(Type t)
    : d(new Private), Component::Component(t)
{
    d->output = new Node;
    d->maxInput = 2;

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
    if(x() - GATE_X_MARGIN < 0)
    {
        setPos(GATE_X_MARGIN, y());
    }
    else if(x() + boundingRect().right() + GATE_X_MARGIN > CANVAS_WIDTH)
    {
        setPos(CANVAS_WIDTH - boundingRect().width() - GATE_X_MARGIN, y());
    }

    if(y() < 0)
    {
        setPos(x(), GATE_Y_MARGIN);
    }
    else if( y()+ boundingRect().bottom() + GATE_Y_MARGIN > CANVAS_HEIGHT)
    {
        setPos(x(), CANVAS_HEIGHT - boundingRect().height() - GATE_Y_MARGIN);
    }
}

QRectF Gate::boundingRect() const
{
    return QRectF(0,0,40,50);
}

} // namespace Logicsim
