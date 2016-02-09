#include <QtWidgets>
#include "gateparts.h"
#include "inputoutputcomponents.h"
#include "inouparts.h"
#include "component.h"

namespace Logicsim {

InputComponent::InputComponent(): Component(Component::InputComponent)
{
    setMetaTypeId(qRegisterMetaType<InputComponent>("InputComponent"));
    InputComponentNode *inN = new InputComponentNode(this);
    ConnectingLine *Li = new ConnectingLine(inN);

    pnode = &inN->GetNodeNode();

    inN->setPos(40,15);
    Li->setPos(-10,2.5);
}

InputComponent::InputComponent(const InputComponent &g):Component(g.componentType())
{
    Q_UNUSED(g);
}

QRectF InputComponent::boundingRect() const
{
    return QRectF(0,0,40,50);
}

void InputComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Component::paint(painter, option, widget);
    painter->drawEllipse(0,0,30,30);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QString InputComponent::imageUrl() const
{
    return QString(":/gates/input");
}

void InputComponent::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
    if(x() - GATE_X_MARGIN < 0)
    {
        setPos(GATE_X_MARGIN, y());
    }
    else if(x() + boundingRect().right() + GATE_X_MARGIN > CANVAS_WIDTH)
    {
        setPos(CANVAS_WIDTH - boundingRect().width() - GATE_X_MARGIN, y());
    }

    if(y() < 0)
    {
        setPos(x(), GATE_Y_MARGIN);
    }
    else if( y()+ boundingRect().bottom() + GATE_Y_MARGIN > CANVAS_HEIGHT)
    {
        setPos(x(), CANVAS_HEIGHT - boundingRect().height() - GATE_Y_MARGIN);
    }
}

void InputComponent::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

Node* InputComponent::GetBodyNode()
{
    return pnode;
}
void InputComponent::SetBodyNode(Node *n)
{
    pnode = n;
}

// ==============================================

OutputComponent::OutputComponent(): Component(Component::OutputComponent)
{
    setMetaTypeId(qRegisterMetaType<OutputComponent>("OutputComponent"));
    OutputComponentNode *outN = new OutputComponentNode(this);
    ConnectingLine *Lo = new ConnectingLine(outN);

    pnode = outN->GetNodeNode();

    outN->setPos(-15,15);
    Lo->setPos(5,2.5);
}

OutputComponent::OutputComponent(const OutputComponent &g): Component(Component::OutputComponent)
{
    Q_UNUSED(g);
}

QRectF OutputComponent::boundingRect() const
{
    return QRectF(0,0,40,50);
}

void OutputComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Component::paint(painter, option, widget);
    painter->drawEllipse(0,0,30,30);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QString OutputComponent::imageUrl() const
{
    return QString(":/gates/output");
}

void OutputComponent::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
    if(x() - GATE_X_MARGIN < 0)
    {
        setPos(GATE_X_MARGIN, y());
    }
    else if(x() + boundingRect().right() + GATE_X_MARGIN > CANVAS_WIDTH)
    {
        setPos(CANVAS_WIDTH - boundingRect().width() - GATE_X_MARGIN, y());
    }

    if(y() < 0)
    {
        setPos(x(), GATE_Y_MARGIN);
    }
    else if( y()+ boundingRect().bottom() + GATE_Y_MARGIN > CANVAS_HEIGHT)
    {
        setPos(x(), CANVAS_HEIGHT - boundingRect().height() - GATE_Y_MARGIN);
    }
}


void OutputComponent::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     Q_UNUSED(event);
    qDebug()<<"Body clicked";

}

Node* OutputComponent::GetBodyNode()
{
    return pnode;
}
void OutputComponent::SetBodyNode(Node *n)
{
    pnode = n;
}

}
