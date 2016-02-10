#include "abstractgate.h"

namespace Logicsim
{

class AbstractGate::Private
{
public:
    Private()
    {
    }
    QString name;
    QList<Node*> input;
    Node*        output;
    qint16       maxInput;
    Type         type;
    int          metaTypeId;
};

AbstractGate::AbstractGate(Type t)
    : d(new Private)
{
    d->type = t;
    d->output = new Node;
    d->maxInput = 2;
}

AbstractGate::~AbstractGate()
{
    delete d;
}

void AbstractGate::setMaxInput(qint16 mi)
{
    d->maxInput = mi;
}

qint16 AbstractGate::maxInput(){
    return d->maxInput;
}

Node* AbstractGate::outputNode()
{
    return d->output;
}

QList<Node*> AbstractGate::inputList() const
{
    return d->input;
}

void AbstractGate::setMetaTypeId(int t)
{
    d->metaTypeId = t;
}

void AbstractGate::setInput(QList<Node *> & n)
{
    d->input = n;
}

AbstractGate::Type AbstractGate::gateType() const
{
    return d->type;
}

int AbstractGate::metaTypeId() const
{
    return d->metaTypeId;
}

QString AbstractGate::name()
{
    return d->name;
}

void AbstractGate::setName(QString value)
{
    d->name = value;
}

} //namespace Logicsim
