#include "inouparts.h"

// Qt includes

#include <QtWidgets>

// Local inlcudes

#include "logicsim_global.h"

namespace Logicsim
{

InputComponentNode::InputComponentNode(QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    node.setValue(false);
}

void InputComponentNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"Input Clicked";
    qDebug()<<"Value of input node: " << node.value();
}

QRectF InputComponentNode::boundingRect() const
{
    return QRectF(0,0,5,5);
}

void InputComponentNode::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawEllipse(0,0,5,5);
}

Node & InputComponentNode::nodeNode()
{
    return node;
}
void InputComponentNode::setNodeNode(Node& n)
{
    node = n;
}

// ==============================================

OutputComponentNode::OutputComponentNode(QGraphicsItem *parent)
    : QGraphicsObject(parent), node(0)
{
    node = 0;
}

void OutputComponentNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"output Clicked";
    qDebug()<<"Value of output node: " << node->value();
}

QRectF OutputComponentNode::boundingRect() const
{
    return QRectF(0,0,5,5);
}

void OutputComponentNode::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawEllipse(0,0,5,5);
}

Node * OutputComponentNode::nodeNode()
{
    return node;
}

void OutputComponentNode::setNodeNode(Node* n)
{
    node = n;
}

} // namespace Logicsim
