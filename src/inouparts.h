#ifndef INOUT
#define INOUT

// Qt includes

#include "node.h"
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

namespace Logicsim
{

class InputComponentBody : public QGraphicsObject
{
private:
    Node *pnode;
public:
   InputComponentBody(QGraphicsItem *parent = 0);
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   QRectF boundingRect() const;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
   Node * GetBodyNode();
   void SetBodyNode(Node *n);
};

// ==============================================

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

// ==============================================

class OutputComponentBody : public QGraphicsObject
{
private:
    Node *pnode;
public:
   OutputComponentBody(QGraphicsItem *parent = 0);
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   QRectF boundingRect() const;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
   Node * GetBodyNode();
   void SetBodyNode(Node *n);
};

// ==============================================

class OutputComponentNode : public QGraphicsObject
{
private:
    Node *node;
public:
    OutputComponentNode(QGraphicsItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    Node* GetNodeNode();
    void SetNodeNode(Node *n);
};

} // namespace Logicsim

#endif // INOUT

