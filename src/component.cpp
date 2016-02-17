#include "component.h"

// Qt includes

#include <QPainter>

// Local includes

#include "logicsim_global.h"
#include "inputoutputcomponents.h"

namespace Logicsim
{

class Component::Private
{
public:
    Private()
        : uniqueId(-1),
          metaTypeId(-1),
          selected(false)

    {}

    quint32         uniqueId;
    int             metaTypeId;
    bool            selected;
    Component::Type type;
    QString         name;
    QList<Pin*>     pins;
};

Component::Component(Type t, QGraphicsItem* parent)
    : QGraphicsObject(parent), d(new Private)
{
    d->type = t;
    d->selected = false;
}

Component::~Component()
{
    delete d;
}

void Component::setMetaTypeId(int t)
{
    d->metaTypeId = t;
}

void Component::addPins(QList<Pin *> &pins)
{
    d->pins << pins;
}

int Component::metaTypeId() const
{
    return d->metaTypeId;
}

quint32 Component::uniqueId() const
{
    return d->uniqueId;
}

void Component::setUniqueId(quint32 id)
{
    d->uniqueId = id;
}

Component::Type Component::componentType() const
{
    return d->type;
}

QRectF Component::boundingRect() const
{
    return QRectF(0,0,40,50);
}

void Component::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(255,255,255,200));

    QPen p;
    p.setWidthF(2);
    if(d->selected)
    {
        p.setColor(QColor(30,144,255));
        painter->setPen(p);
    }
    else
    {
        p.setColor(Qt::black);
        painter->setPen(p);
    }
}

QList<Pin *> &Component::pins()
{
    return d->pins;
}

void Component::setSelection(bool selection)
{
    d->selected = selection;
    update();
}

QString Component::name()
{
    return d->name;
}

void Component::setName(QString name)
{
    d->name = name;
    setToolTip(name);
}

QDataStream &operator<<(QDataStream &out, Component * c)
{
    out << c->uniqueId()
        << static_cast<qint32>(c->componentType())
        << QPoint(c->pos().x(), c->pos().y())
        << c->name();
    return out;
}

QDataStream &operator>>(QDataStream &in, Component *& c)
{
    qint32 id, t;
    QPoint pos;
    QString name;
    in >> id >> t >> pos >> name;
    switch(t)
    {
        case Component::AndGate:
            c = new AndGate();
            break;
        case Component::OrGate:
            c = new OrGate();
            break;
        case Component::NotGate:
            c = new NotGate();
            break;
        case Component::NandGate:
            c = new NandGate();
            break;
        case Component::NorGate:
            c = new NorGate();
        case Component::XorGate:
            c = new XorGate();
            break;
        case Component::XnorGate:
            c = new XnorGate();
            break;
        case Component::InputComponent:
            c = new InputComponent();
            break;
        case Component::OutputComponent:
            c = new OutputComponent();
            break;
    }
    c->setUniqueId(id);
    c->setPos(pos);
    c->setName(name);
    return in;
}

} // namespace Logicsim
