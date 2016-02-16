#ifndef COMPONENT_H
#define COMPONENT_H

// Qt includes

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>

// Local includes

#include "pin.h"

namespace Logicsim
{

class Pin;

class Component: public QGraphicsObject
{
public:
    enum Type
    {
        AndGate = 0,
        OrGate,
        NotGate,
        NandGate,
        NorGate,
        XorGate,
        XnorGate,
        InputComponent,
        OutputComponent
    };

public:
    ~Component();

    Type componentType() const;

    QString name();
    int metaTypeId() const;
    virtual QString imageUrl() const = 0;
    void setSelection(bool selection);
    void setName(QString name);

    QRectF boundingRect() const;
    virtual void updateConnection() = 0;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QList<Pin *> &pins();

protected:
    Component(Type t, QGraphicsItem *parent = 0);
    void setMetaTypeId(int t);
    void addPins(QList<Pin*>& pins);

private:
    class Private;
    Private* const d;
};

QDataStream &operator<<(QDataStream &out, Component * c);
QDataStream &operator>>(QDataStream &in, Component *& c);

} // namespace Logicsim

#endif // COMPONENT
