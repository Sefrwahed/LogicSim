#include <QtWidgets>
#include "drawablegenericgate.h"

Logicsim::Part::Part(QGraphicsItem *parent): QGraphicsObject(parent)
{}

Logicsim::GateBody::GateBody(QGraphicsItem *parent):Part(parent)
{}

void Logicsim::GateBody::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     Q_UNUSED(event);
}

QRectF Logicsim::GateBody::boundingRect() const
{
    return QRectF(0,0,40,50);
}

void Logicsim::GateBody::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawRect(0,0,40,50);
}

Logicsim::Input::Input(QGraphicsItem *parent):Part(parent)
{}

void Logicsim::Input::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"Input Clicked";
}

QRectF Logicsim::Input::boundingRect() const
{
    return QRectF(0,0,5,5);
}

void Logicsim::Input::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawEllipse(0,0,5,5);
}

Logicsim::Output::Output(QGraphicsItem *parent):Part(parent)
{}

void Logicsim::Output::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"Output Clicked";
}

QRectF Logicsim::Output::boundingRect() const
{
    return QRectF(0,0,5,5);
}

void Logicsim::Output::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawEllipse(0,0,5,5);
}

Logicsim::Gate::Gate(QGraphicsItem *parent)
{
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

QRectF Logicsim::Gate::boundingRect() const
{
    return QRectF();
}

void Logicsim::Gate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

Logicsim::ConnectingLine::ConnectingLine(QGraphicsItem *parent):Part(parent)
{}

QRectF Logicsim::ConnectingLine::boundingRect() const
{
    return QRectF(0,0,10,0);
}

void Logicsim::ConnectingLine::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawLine(0,0,10,0);
}
