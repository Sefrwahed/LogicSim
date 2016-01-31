#ifndef INPUTOUTPUTCOMPONENTS
#define INPUTOUTPUTCOMPONENTS

#include "node.h"
#include "gateparts.h"
#include <QtWidgets>

namespace Logicsim
{

/*Input*/
class Component
{

public:
    Component();
    int metaTypeId() const;
protected:
    void setMetaTypeId(int t);
private:
    class Private;
    Private* const d;
};

class InputComponentBody : public QGraphicsObject
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

class InputComponentNode : public QGraphicsObject
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

class InputComponent : public QGraphicsObject,public Component
{
public:
    InputComponent(QGraphicsItem *parent = 0);
    InputComponent(const InputComponent& g);
    InputComponent(double xPos, double yPos, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

/*Output*/

class OutputComponentBody : public QGraphicsObject
{
private:
    Node *pnode;
public:
   OutputComponentBody(QGraphicsItem *parent = 0);
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
   QRectF boundingRect() const;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
   Node * GetBodyNode();
   void SetBodyNode(Node *n);


};

class OutputComponentNode : public QGraphicsObject
{
private:
    Node *node;
    //Node n;
public:
    OutputComponentNode(QGraphicsItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    Node* GetNodeNode();
    void SetNodeNode(Node *n);
};

class OutputComponent : public QGraphicsObject,public Component
{
public:
    OutputComponent(QGraphicsItem *parent = 0);
    OutputComponent(const OutputComponent& g);
    OutputComponent(double xPos, double yPos, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

}

#endif // INPUTOUTPUTCOMPONENTS

