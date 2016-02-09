#ifndef INPUTOUTPUTCOMPONENTS
#define INPUTOUTPUTCOMPONENTS

#include "node.h"
#include "inouparts.h"
#include "gateparts.h"
#include "component.h"
#include "logicsim_global.h"
#include <QtWidgets>

namespace Logicsim
{
class InputComponent : public Component
{
private:
    Node *pnode;
public:
    InputComponent();
    InputComponent(const InputComponent& g);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QString imageUrl() const;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //QRectF boundingRect() const;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    Node * GetBodyNode();
    void SetBodyNode(Node *n);
};


class OutputComponent : public Component
{ 
private:
    Node *pnode;
public:
    OutputComponent();
    OutputComponent(const OutputComponent& g);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QString imageUrl() const;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    Node * GetBodyNode();
    void SetBodyNode(Node *n);
};

}

#endif // INPUTOUTPUTCOMPONENTS

