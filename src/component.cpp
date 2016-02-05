#include "graphicgate.h"

// Local includes

#include "component.h"
#include "logicsim_global.h"

namespace Logicsim
{

class Component::Private
{
public:
    Private()
    {}

    int metaTypeId;
};

Component::Component()
    : d(new Private)
{}

void Component::setMetaTypeId(int t)
{
    d->metaTypeId = t;
}

int Component::metaTypeId() const
{
    return d->metaTypeId;
}

} // namespace Logicsim
