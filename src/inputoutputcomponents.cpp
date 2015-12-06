#include <QtWidgets>
#include "inputoutputcomponents.h"

namespace Logicsim {

const int X_MARGIN = 20;
const int CANVAS_WIDTH = 1500;
const int CANVAS_HEIGHT = 1500;


/*Input component's Body*/

InputComponentBody::InputComponentBody(QGraphicsItem *parent):Part(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void InputComponentBody::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     Q_UNUSED(event);
    if(pnode->getValue()==false){
       pnode->setValue(true);
    }else if(pnode->getValue() == true) {
        pnode->setValue(false);
    }
    qDebug()<<"Body clicked";
    qDebug()<<"input changed to : "<<pnode->getValue();
}

void InputComponentBody::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
    if(x() - X_MARGIN < 0)
    {
        setPos(X_MARGIN, y());
    }
    else if(x() + boundingRect().right() + X_MARGIN > CANVAS_WIDTH)
    {
        setPos(CANVAS_WIDTH - boundingRect().width() - X_MARGIN, y());
    }

    if(y() < 0)
    {
        setPos(x(), 0);
    }
    else if( y()+ boundingRect().bottom() > CANVAS_HEIGHT)
    {
        setPos(x(), CANVAS_HEIGHT - boundingRect().height());
    }
}

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

/*Input component's Node*/

InputComponentNode::InputComponentNode(QGraphicsItem *parent):Part(parent)
{
    node.setValue(false);
}

void InputComponentNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"Input Clicked";
    qDebug()<<"Value of input node: " << node.getValue();
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

/*Input component*/

InputComponent::InputComponent(QGraphicsItem *parent)
{
    Q_UNUSED(parent);
    InputComponentBody *inB = new InputComponentBody(this);
    InputComponentNode *inN = new InputComponentNode(inB);
    ConnectingLine *Li = new ConnectingLine(inN);

    inB->SetBodyNode(&inN->GetNodeNode());

    inB->setPos(50,50);
    inN->setPos(40,15);
    Li->setPos(-10,2.5);
}

InputComponent::InputComponent(double xPos, double yPos, QGraphicsItem *parent)
{
    qDebug() << xPos << "," << yPos;
    Q_UNUSED(parent);
    InputComponentBody *inB = new InputComponentBody(this);
    InputComponentNode *inN = new InputComponentNode(inB);
    ConnectingLine *Li = new ConnectingLine(inN);

    inB->SetBodyNode(&inN->GetNodeNode());

    xPos -= inB->boundingRect().width()/2;
    yPos -= inB->boundingRect().height()/2;
    inB->setPos(xPos,yPos);
    inN->setPos(40,15);
    Li->setPos(-10,2.5);
}

QRectF InputComponent::boundingRect() const
{
    return QRectF();
}

void InputComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

/*Output component's Body*/

OutputComponentBody::OutputComponentBody(QGraphicsItem *parent):Part(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void OutputComponentBody::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     Q_UNUSED(event);
    qDebug()<<"Body clicked";
    qDebug()<<"output is : "<<pnode->getValue();
}

void OutputComponentBody::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
    if(x() - X_MARGIN < 0)
    {
        setPos(X_MARGIN, y());
    }
    else if(x() + boundingRect().right() + X_MARGIN > CANVAS_WIDTH)
    {
        setPos(CANVAS_WIDTH - boundingRect().width() - X_MARGIN, y());
    }

    if(y() < 0)
    {
        setPos(x(), 0);
    }
    else if( y()+ boundingRect().bottom() > CANVAS_HEIGHT)
    {
        setPos(x(), CANVAS_HEIGHT - boundingRect().height());
    }
}

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

/*output component's Node*/

OutputComponentNode::OutputComponentNode(QGraphicsItem *parent):Part(parent)
{
    node.setValue(false);
}

void OutputComponentNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"output Clicked";
    qDebug()<<"Value of output node: " << node.getValue();
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

Node & OutputComponentNode::GetNodeNode()
{
    return node;
}
void OutputComponentNode::SetNodeNode(Node& n)
{
    node = n;
}

/*Output component*/

OutputComponent::OutputComponent(QGraphicsItem *parent)
{
    Q_UNUSED(parent);
    OutputComponentBody *outB = new OutputComponentBody(this);
    OutputComponentNode *outN = new OutputComponentNode(outB);
    ConnectingLine *Lo = new ConnectingLine(outN);

    outB->SetBodyNode(&outN->GetNodeNode());

    outN->setPos(-15,15);
    Lo->setPos(5,2.5);
}

OutputComponent::OutputComponent(double xPos, double yPos, QGraphicsItem *parent)
{
    qDebug() << xPos << "," << yPos;
    Q_UNUSED(parent);
    OutputComponentBody *outB = new OutputComponentBody(this);
    OutputComponentNode *outN = new OutputComponentNode(outB);
    ConnectingLine *Lo = new ConnectingLine(outN);

    outB->SetBodyNode(&outN->GetNodeNode());

    xPos -= outB->boundingRect().width()/2;
    yPos -= outB->boundingRect().height()/2;
    outB->setPos(xPos,yPos);
    outN->setPos(-15,15);
    Lo->setPos(5,2.5);
}

QRectF OutputComponent::boundingRect() const
{
    return QRectF();
}

void OutputComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


}
