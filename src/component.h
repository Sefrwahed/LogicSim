#ifndef COMPONENT_H
#define COMPONENT_H

// Qt includes

#include <QGraphicsObject>

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
