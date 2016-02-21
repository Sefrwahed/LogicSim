#ifndef PIN_H
#define PIN_H

// Local includes

#include "connectionline.h"
#include "component.h"

// Qt includes

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

namespace Logicsim
{
class Component;
class ConnectionLine;

class Pin : public QGraphicsObject
{
    Q_OBJECT

public:
    enum Type {
        Input,
        Output
    };

    enum Value {
        True,
        False,
        Undefined
    };

public:
    Pin(Type t, Component *parent = 0);
    ~Pin();

    bool isConnected();
    void setConnected(ConnectionLine* line);

    void setNumber(quint32 n);
    quint32 number() const;

    void updateConnectedLine();
    QList<ConnectionLine *> &connectedLines();

    Pin::Value value();

    QPointF centerPos() const;

    int type() const;
    Component *parentComponent() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

public Q_SLOTS:
    void disconnectLine();
    void updatePinValue(Pin::Value value);

Q_SIGNALS:
    void changed(Pin::Value v);

private:
    Value                  m_value;
    quint32                m_number;
    Type                   m_type;
    Component*             m_parent;
    QList<ConnectionLine*> m_lines;
};

} // namespace Logicsim

#endif // DRAWABLEGENERICGATE

