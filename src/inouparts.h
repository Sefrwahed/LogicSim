#ifndef INOUT
#define INOUT

// Local includes

#include "node.h"

// Qt includes

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

namespace Logicsim
{
class InputComponentNode : public QGraphicsObject
{
public:
    InputComponentNode(QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    Node& nodeNode();
    void setNodeNode(Node &n);

private:
    Node node;
};

// ==============================================

class OutputComponentNode : public QGraphicsObject
{
public:
    OutputComponentNode(QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    Node* nodeNode();
    void setNodeNode(Node *n);

private:
    Node *node;
};

} // namespace Logicsim

#endif // INOUT

