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
        OutputComponent
    };

    int metaTypeId() const;
    virtual QString imageUrl() const = 0;
    Type componentType() const;
    ~Component();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setSelection(bool selection);
    QString name();
    void setName(QString name);

protected:
    Component(Type t);
    void setMetaTypeId(int t);

private:
    class Private;
    Private* const d;
};

} // namespace Logicsim

#endif // COMPONENT
