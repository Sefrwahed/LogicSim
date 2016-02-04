#ifndef COMPONENT
#define COMPONENT

// Qt includes

#include <QGraphicsObject>

// Local includes

#include "abstractgate.h"

namespace Logicsim
{
class Component: public QGraphicsObject
{
public:
    Component();
    int metaTypeId() const;
    virtual QString imageUrl() const = 0;
protected:
    void setMetaTypeId(int t);
private:
    class Private;
    Private* const d;
};


} // namespace Logicsim

#endif // COMPONENT
