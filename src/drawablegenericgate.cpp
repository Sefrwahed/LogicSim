#include <QtWidgets>
#include "drawablegenericgate.h"

namespace Logicsim
{
const int X_MARGIN = 20;
const int CANVAS_WIDTH = 1500;
const int CANVAS_HEIGHT = 1500;
Part::Part(QGraphicsItem *parent): QGraphicsObject(parent)
{}

GateBody::GateBody(QGraphicsItem *parent):Part(parent)
{
    //setFlag(QGraphicsItem::ItemIsSelectable); //item must be selected first before dragging
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void GateBody::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     Q_UNUSED(event);
}

void GateBody::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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

QRectF GateBody::boundingRect() const
{
    return QRectF(0,0,40,50);
}

void GateBody::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawRect(0,0,40,50);
}

Input::Input(QGraphicsItem *parent):Part(parent)
{}

void Input::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"Input Clicked";
}

QRectF Input::boundingRect() const
{
    return QRectF(0,0,5,5);
}

void Input::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawEllipse(0,0,5,5);
}

Output::Output(QGraphicsItem *parent):Part(parent)
{}

void Output::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"Output Clicked";
}

QRectF Output::boundingRect() const
{
    return QRectF(0,0,5,5);
}

void Output::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawEllipse(0,0,5,5);
}

GraphicGate::GraphicGate(QGraphicsItem *parent)
{
    Q_UNUSED(parent);
    QGraphicsObject *gate = new GateBody(this);
    QGraphicsObject *in1 = new Input(gate);
    QGraphicsObject *in2 = new Input(gate);
    QGraphicsObject *out1 = new Output(gate);

    QGraphicsObject *Li1 = new ConnectingLine(in1);
    QGraphicsObject *Li2 = new ConnectingLine(in2);
    QGraphicsObject *Lo1 = new ConnectingLine(out1);

    gate->setPos(50,50);
    in1->setPos(-15,15);
    in2->setPos(-15,35);
    out1->setPos(50,25);
    Li1->setPos(5,2.5);
    Li2->setPos(5,2.5);
    Lo1->setPos(-10,2.5);
}

GraphicGate::GraphicGate(double xPos, double yPos, QGraphicsItem *parent)
{

    qDebug() << xPos << "," << yPos;
    Q_UNUSED(parent);
    QGraphicsObject *gate = new GateBody(this);
    QGraphicsObject *in1 = new Input(gate);
    QGraphicsObject *in2 = new Input(gate);
    QGraphicsObject *out1 = new Output(gate);

    QGraphicsObject *Li1 = new ConnectingLine(in1);
    QGraphicsObject *Li2 = new ConnectingLine(in2);
    QGraphicsObject *Lo1 = new ConnectingLine(out1);
    gate->setPos(xPos, yPos);
    in1->setPos(-15,15);
    in2->setPos(-15,35);
    out1->setPos(50,25);
    Li1->setPos(5,2.5);
    Li2->setPos(5,2.5);
    Lo1->setPos(-10,2.5);
}

QRectF GraphicGate::boundingRect() const
{
    return QRectF();
}

void GraphicGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

ConnectingLine::ConnectingLine(QGraphicsItem *parent):Part(parent)
{}

QRectF ConnectingLine::boundingRect() const
{
    return QRectF(0,0,10,0);
}

void ConnectingLine::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawLine(0,0,10,0);
}
}
