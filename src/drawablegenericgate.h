#ifndef DRAWABLEGENERICGATE
#define DRAWABLEGENERICGATE

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <qdebug.h>

namespace Logicsim
{
class Part : public QGraphicsObject
{
public:
    Part(QGraphicsItem *parent = 0);
};

class GateBody : public Part
{
public:
   GateBody(QGraphicsItem *parent = 0);
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   QRectF boundingRect() const;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

class Input : public Part
{
public:
    Input(QGraphicsItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

class Output : public Part
{
public:
    Output(QGraphicsItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

class Gate : public Part
{
public:
    Gate(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

class ConnectingLine : public Part
{
public:
    ConnectingLine(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

}

#endif // DRAWABLEGENERICGATE

