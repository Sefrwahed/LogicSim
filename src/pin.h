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

class ConnectionLine;

class Pin : public QGraphicsObject
{
public:
    enum Type {
        Input,
        Output
    };

public:
    Pin(Type t, Component *parent = 0);
    ~Pin();

    bool isConnected();
    void setConnected(ConnectionLine* line);

    void updateConnectedLine();

    QPointF centerPos() const;

    int type() const;
    Component *parentComponent() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    Type m_type;
    ConnectionLine* m_line;
    Component* m_parent;
};

} // namespace Logicsim

#endif // DRAWABLEGENERICGATE

