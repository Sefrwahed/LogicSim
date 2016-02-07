#include <QtWidgets>
#include "gateparts.h"
#include "inputoutputcomponents.h"
#include "inouparts.h"
#include "component.h"

namespace Logicsim {

InputComponent::InputComponent(QGraphicsItem *parent): Component(Component::InputComponent)
{
    setMetaTypeId(qRegisterMetaType<InputComponent>("InputComponent"));
    Q_UNUSED(parent);
    InputComponentBody *inB = new InputComponentBody(this);
    InputComponentNode *inN = new InputComponentNode(inB);
    ConnectingLine *Li = new ConnectingLine(inN);

    inB->SetBodyNode(&inN->GetNodeNode());

    inB->setPos(50,50);
    inN->setPos(40,15);
    Li->setPos(-10,2.5);
}

InputComponent::InputComponent(const InputComponent &g):Component(g.componentType())
{Q_UNUSED(g);}

InputComponent::InputComponent(double xPos, double yPos, QGraphicsItem *parent): Component(Component::InputComponent)
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
    return QRectF(0,0,40,50);
}

void InputComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
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

// ==============================================

OutputComponent::OutputComponent(QGraphicsItem *parent): Component(Component::OutputComponent)
{
    Q_UNUSED(parent);
    setMetaTypeId(qRegisterMetaType<OutputComponent>("OutputComponent"));
    OutputComponentBody *outB = new OutputComponentBody(this);
    OutputComponentNode *outN = new OutputComponentNode(outB);
    ConnectingLine *Lo = new ConnectingLine(outN);

    outB->SetBodyNode(outN->GetNodeNode());
    //outB->SetBodyNode(&outN->GetNodeNode());

    outN->setPos(-15,15);
    Lo->setPos(5,2.5);
}

OutputComponent::OutputComponent(const OutputComponent &g): Component(Component::OutputComponent)
{Q_UNUSED(g);}

OutputComponent::OutputComponent(double xPos, double yPos, QGraphicsItem *parent): Component(Component::OutputComponent)
{
    qDebug() << xPos << "," << yPos;
    Q_UNUSED(parent);
    OutputComponentBody *outB = new OutputComponentBody(this);
    OutputComponentNode *outN = new OutputComponentNode(outB);
    ConnectingLine *Lo = new ConnectingLine(outN);

    outB->SetBodyNode(outN->GetNodeNode());

    xPos -= outB->boundingRect().width()/2;
    yPos -= outB->boundingRect().height()/2;
    outB->setPos(xPos,yPos);
    outN->setPos(-15,15);
    Lo->setPos(5,2.5);
}

QRectF OutputComponent::boundingRect() const
{
    return QRectF(0,0,40,50);
}

void OutputComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
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

}
