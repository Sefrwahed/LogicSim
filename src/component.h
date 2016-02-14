#ifndef COMPONENT_H
#define COMPONENT_H

// Qt includes

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>

namespace Logicsim
{

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
        OutputComponent,
        ConnectionLine
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

protected:
    Component(Type t);
    void setMetaTypeId(int t);

private:
    class Private;
    Private* const d;
};

} // namespace Logicsim

#endif // COMPONENT
