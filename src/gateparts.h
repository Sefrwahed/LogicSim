#ifndef DRAWABLEGENERICGATE
#define DRAWABLEGENERICGATE

// Qt includes

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

namespace Logicsim
{

class Input : public QGraphicsObject
{
public:
    Input(QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

// ==============================================

class Output : public QGraphicsObject
{
public:
    Output(QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

// ==============================================

class ConnectingLine : public QGraphicsObject
{
public:
    ConnectingLine(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

} // namespace Logicsim

#endif // DRAWABLEGENERICGATE

