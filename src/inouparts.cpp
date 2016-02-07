#include "inouparts.h"

// Qt includes

#include <QtWidgets>

// Local inlcudes

#include "logicsim_global.h"

namespace Logicsim
{
const int X_MARGIN = 20;

InputComponentBody::InputComponentBody(QGraphicsItem *parent):QGraphicsObject(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void InputComponentBody::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     Q_UNUSED(event);
    if(pnode->value()==false){
       pnode->setValue(true);
    }else if(pnode->value() == true) {
        pnode->setValue(false);
    }
    qDebug()<<"Body clicked";
    qDebug()<<"input changed to : "<<pnode->value();
}

//void InputComponentBody::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    QGraphicsObject::mouseMoveEvent(event);
//    if(x() - GATE_X_MARGIN < 0)
//    {
//        setPos(GATE_X_MARGIN, y());
//    }
//    else if(x() + boundingRect().right() + GATE_X_MARGIN > CANVAS_WIDTH)
//    {
//        setPos(CANVAS_WIDTH - boundingRect().width() - GATE_X_MARGIN, y());
//    }

//    if(y() < 0)
//    {
//        setPos(x(), GATE_Y_MARGIN);
//    }
//    else if( y()+ boundingRect().bottom() + GATE_Y_MARGIN > CANVAS_HEIGHT)
//    {
//        setPos(x(), CANVAS_HEIGHT - boundingRect().height() - GATE_Y_MARGIN);
//    }
//}

QRectF InputComponentBody::boundingRect() const
{
    return QRectF(0,0,30,30);
}

void InputComponentBody::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawEllipse(0,0,30,30);
}

Node* InputComponentBody::GetBodyNode()
{
    return pnode;
}
void InputComponentBody::SetBodyNode(Node *n)
{
    pnode = n;
}

// ==============================================

InputComponentNode::InputComponentNode(QGraphicsItem *parent):QGraphicsObject(parent)
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

Node & InputComponentNode::GetNodeNode()
{
    return node;
}
void InputComponentNode::SetNodeNode(Node& n)
{
    node = n;
}

// ==============================================

OutputComponentBody::OutputComponentBody(QGraphicsItem *parent):QGraphicsObject(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void OutputComponentBody::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     Q_UNUSED(event);
    qDebug()<<"Body clicked";
    qDebug()<<"output is : "<<pnode->value();
}

//void OutputComponentBody::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    QGraphicsObject::mouseMoveEvent(event);
//    if(x() - GATE_X_MARGIN < 0)
//    {
//        setPos(GATE_X_MARGIN, y());
//    }
//    else if(x() + boundingRect().right() + GATE_X_MARGIN > CANVAS_WIDTH)
//    {
//        setPos(CANVAS_WIDTH - boundingRect().width() - GATE_X_MARGIN, y());
//    }

//    if(y() < 0)
//    {
//        setPos(x(), GATE_Y_MARGIN);
//    }
//    else if( y()+ boundingRect().bottom() + GATE_Y_MARGIN > CANVAS_HEIGHT)
//    {
//        setPos(x(), CANVAS_HEIGHT - boundingRect().height() - GATE_Y_MARGIN);
//    }
//}

QRectF OutputComponentBody::boundingRect() const
{
    return QRectF(0,0,30,30);
}

void OutputComponentBody::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawEllipse(0,0,30,30);
}

Node* OutputComponentBody::GetBodyNode()
{
    return pnode;
}
void OutputComponentBody::SetBodyNode(Node *n)
{
    pnode = n;
}

// ==============================================

OutputComponentNode::OutputComponentNode(QGraphicsItem *parent):QGraphicsObject(parent)
{
    //node->setValue(false);
//    n.setValue(false);
//    node = &n;
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

Node * OutputComponentNode::GetNodeNode()
{
    return node;
}
void OutputComponentNode::SetNodeNode(Node* n)
{
    node = n;
}

} // namespace Logicsim
