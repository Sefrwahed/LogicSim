#include "component.h"

// Local includes

#include "logicsim_global.h"

namespace Logicsim
{

class Component::Private
{
public:
    Private()
    {}

    int metaTypeId;
    Component::Type   type;
};

Component::Component(Type t)
    : d(new Private)
{d->type = t;}


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

} // namespace Logicsim
