#ifndef INPUTOUTPUTCOMPONENTS
#define INPUTOUTPUTCOMPONENTS

#include "drawablegenericgate.h"
#include "node.h"
#include <QtWidgets>

namespace Logicsim
{

class InputComponentBody : public Part
{
private:
    Node *pnode;
public:
   InputComponentBody(QGraphicsItem *parent = 0);
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
   QRectF boundingRect() const;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
   Node * GetBodyNode();
   void SetBodyNode(Node *n);


};

class InputComponentNode : public Part
{
private:
    Node node;
public:
    InputComponentNode(QGraphicsItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    Node& GetNodeNode();
    void SetNodeNode(Node &n);
};

class InputComponent : public Part
{
public:
    InputComponent(QGraphicsItem *parent = 0);
    InputComponent(double xPos, double yPos, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

class OutputComponent : public Part
{
public:
    OutputComponent(QGraphicsItem *parent = 0);
    OutputComponent(double xPos, double yPos, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

}

#endif // INPUTOUTPUTCOMPONENTS

