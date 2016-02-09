#include "component.h"

// Local includes

#include "logicsim_global.h"

#include <QPainter>

namespace Logicsim
{

class Component::Private
{
public:
    Private()
    {}

    int metaTypeId;
    Component::Type type;
    bool selected;
    QString name;
};

Component::Component(Type t)
    : d(new Private)
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

int Component::metaTypeId() const
{
    return d->metaTypeId;
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
    if(d->selected)
    {
        painter->setPen(QPen(QColor(123,183,243),2));
    }
    else
    {
        painter->setPen(QPen(Qt::black));
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
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
}

} // namespace Logicsim
