#ifndef INPUTOUTPUTCOMPONENTS
#define INPUTOUTPUTCOMPONENTS

#include "drawablegenericgate.h"
#include "node.h"

namespace Logicsim
{

class InputComponentBody : public Part
{
public:
   InputComponentBody(QGraphicsItem *parent = 0);
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
   QRectF boundingRect() const;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};

class InputComponentNode : public Part
{
public:
    InputComponentNode(QGraphicsItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

class InputComponent : public Part
{
public:
    InputComponent(QGraphicsItem *parent = 0);
    InputComponent(double xPos, double yPos, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

}

#endif // INPUTOUTPUTCOMPONENTS

