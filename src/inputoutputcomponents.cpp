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
    return QRectF();
}

void InputComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
//**/////////////////////////////Not yet implemented///////////////////////////**//
QString InputComponent::imageUrl() const
{
    return QString("");
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
    return QRectF();
}

void OutputComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
//**/////////////////////////////Not yet implemented///////////////////////////**//
QString OutputComponent::imageUrl() const
{
    return QString("");
}


}
