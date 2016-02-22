#include "gates.h"
#include <string>

// Qt includes

#include <QDebug>
#include <QPainter>
#include <QTimer>

// Local includes

#include "delaysdialog.h"

namespace Logicsim
{

// ===================== AndGate ===================

AndGate::AndGate()
    :Gate(Component::AndGate)
{
    setMetaTypeId(qRegisterMetaType<AndGate>("AndGate"));
    setToolTip("And Gate");
}

AndGate::AndGate(const AndGate &g)
    : Gate(g.componentType())
{
}

QRectF AndGate::boundingRect() const
{
    return Component::boundingRect();
}

void AndGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Gate::paint(painter, option, widget);
    QPainterPath path(QPointF(0,0));
    path.arcTo(QRect(0,0,40,50), 90, -180);
    path.lineTo(20,50);
    path.lineTo(0,50);
    path.lineTo(0,0);
    painter->drawPath(path);
}

void AndGate::calcOutput()
{
//    Pin::Value out_logic;
    /*
    foreach (Node * n, inputList())
    {
        out_logic &= n->value();
    }*/

    //out_logic = d->
    //outputNode()->setValue(out);
    if(in1()->value() == Pin::True && in2()->value() == Pin::True)
    {
        out_logic = Pin::True;
    }
    else if(in1()->value() == Pin::Undefined || in2()->value() == Pin::Undefined)
    {
        out_logic = Pin::Undefined;
    }
    else
    {
        out_logic = Pin::False;
    }
    qDebug() << "calculate AND called";
    qDebug() << out_logic;
    //emit outputChanged(out_logic);
    QTimer::singleShot(DelaysDialog::instance()->gateDelay(componentType()),
                       this,
                       SLOT(outputCalculated()));
}

QString AndGate::imageUrl() const
{
    return QString(":/gates/and");
}

// ===================== OrGate ===================


OrGate::OrGate()
    : Gate(Component::OrGate)
{
    setMetaTypeId(qRegisterMetaType<OrGate>("OrGate"));
    setToolTip("Or Gate");
}

OrGate::OrGate(const OrGate &g)
    : Gate(g.componentType())
{
}

void OrGate::calcOutput()
{
    Pin::Value out_logic;
    /*foreach (Node * n, inputList())
    {
        out_logic |= n->value();
    }*/
    if(in1()->value() == Pin::False && in2()->value() == Pin::False)
    {
        out_logic = Pin::False;
    }
    else if(in1()->value() == Pin::True || in2()->value() == Pin::True)
    {
        out_logic = Pin::True;
    }
    else
    {
        out_logic = Pin::Undefined;
    }
    qDebug() << "calculate OR called";
    qDebug() << out_logic;

    //outputNode()->setValue(out);
    emit outputChanged(out_logic);
}

QString OrGate::imageUrl() const
{
    return QString(":/gates/or");
}

QRectF OrGate::boundingRect() const
{
    return Component::boundingRect();
}

void OrGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Gate::paint(painter, option, widget);
    QPainterPath path;
    path.arcMoveTo(QRect(-22,-5,25,60), -50);
    path.arcTo(QRect(-30,-2,70,50), -100, 93.75);
    path.arcTo(QRect(-30,4,70,50), 6.25, 93.75);
    path.arcTo(QRect(-22,-5,25,60), 43.75, -93.75);
    painter->drawPath(path);
}



// ===================== NotGate ===================

NotGate::NotGate()
    : Gate(Component::NotGate)
{
    setMaxInput(1);
    setMetaTypeId(qRegisterMetaType<NotGate>("NotGate"));
    setToolTip("Not Gate");
}

NotGate::NotGate(const NotGate &g)
    : Gate(g.componentType())
{
}

void NotGate::calcOutput()
{
    Pin::Value out_logic;
    if(in1()->value() == Pin::False)
    {
        out_logic = Pin::True;
    }
    else if(in1()->value() == Pin::True)
    {
        out_logic = Pin::False;
    }
    else
    {
        out_logic = Pin::Undefined;
    }
    emit outputChanged(out_logic);
}

QString NotGate::imageUrl() const
{
    return QString(":/gates/not");
}

QRectF NotGate::boundingRect() const
{
    return Component::boundingRect();
}

void NotGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Gate::paint(painter, option, widget);
    QPainterPath path(QPointF(35,27));
    path.lineTo(0,50);
    path.lineTo(0,0);
    path.lineTo(35,27);
    path.addEllipse(35,25,5,5);
    painter->drawPath(path);
}

// ===================== NandGate ===================

NandGate::NandGate()
    : Gate(Component::NandGate)
{
    setMetaTypeId(qRegisterMetaType<NandGate>("NandGate"));
    setToolTip("Nand Gate");
}

NandGate::NandGate(const NandGate &g)
    : Gate(g.componentType())
{
}

void NandGate::calcOutput()
{
    Pin::Value out_logic;
    /*foreach (Node * n, inputList())
    {
        out_logic &= n->value();

    }
    */
    if(in1()->value() == Pin::True && in2()->value() == Pin::True)
    {
        out_logic = Pin::True;
    }
    else if(in1()->value() == Pin::Undefined || in2()->value() == Pin::Undefined)
    {
        out_logic = Pin::Undefined;
    }
    else
    {
        out_logic = Pin::False;
    }
    qDebug() << "calculate NAND called";
    if(out_logic == Pin::False)
    {
        out_logic = Pin::True;
    }
    else if(out_logic == Pin::True)
    {
        out_logic = Pin::False;
    }
    else
    {
        out_logic = Pin::Undefined;
    }
    qDebug() << out_logic;
    //outputNode()->setValue(!out);
    emit outputChanged(out_logic);
}

QString NandGate::imageUrl() const
{
    return QString(":/gates/nand");
}


void NandGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Gate::paint(painter, option, widget);
    QPainterPath path(QPointF(0,0));
    path.arcTo(QRect(-4,0,40,50), 90, -90);
    path.arcTo(QRect(36,25,5,5), 180, -360);
    path.arcTo(QRect(-4,0,40,50), 0, -90);
    path.lineTo(20,50);
    path.lineTo(0,50);
    path.lineTo(0,0);
    painter->drawPath(path);
}

// ===================== NorGate ===================

NorGate::NorGate()
    : Gate(Component::NorGate)
{
    setMetaTypeId(qRegisterMetaType<NorGate>("NorGate"));
    setToolTip("Nor Gate");
}

NorGate::NorGate(const NorGate &g)
    : Gate(g.componentType())
{
}

void NorGate::calcOutput()
{
    Pin::Value out_logic;
    /*foreach (Node * n, inputList())
    {
        out_logic |= n->value();

    }
    */
    if(in1()->value() == Pin::False && in2()->value() == Pin::False)
    {
        out_logic = Pin::False;
    }
    else if(in1()->value() == Pin::True || in2()->value() == Pin::True)
    {
        out_logic = Pin::True;
    }
    else
    {
        out_logic = Pin::Undefined;
    }
    if(out_logic == Pin::False)
    {
        out_logic = Pin::True;
    }
    else if(out_logic == Pin::True)
    {
        out_logic = Pin::False;
    }
    else
    {
        out_logic = Pin::Undefined;
    }
    qDebug() << "calculate NOR called";
    qDebug() << out_logic;


    //outputNode()->setValue(!out);
    emit outputChanged(out_logic);
}

QString NorGate::imageUrl() const
{
    return QString(":/gates/nor");
}

void NorGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Gate::paint(painter, option, widget);
    QPainterPath path;
    path.arcMoveTo(QRect(-22,-5,25,60), -50);
    path.arcTo(QRect(-22,-2,60,50), -106.25, 93.75);
    path.arcTo(QRect(36,25,5,5), 180, -360);
    path.arcTo(QRect(-22,4,60,50), 12.5, 93.75);
    path.arcTo(QRect(-22,-5,25,60), 43.75, -93.75);
    painter->drawPath(path);
}

// ===================== XorGate ===================

XorGate::XorGate()
    : Gate(Component::XorGate)
{
    setMetaTypeId(qRegisterMetaType<XorGate>("XorGate"));
    setToolTip("Xor Gate");
}

XorGate::XorGate(const XorGate &g)
    : Gate(g.componentType())
{
}

void XorGate::calcOutput()
{
    Pin::Value out_logic;// = inputList()[0]->value();
    /*outputNode()->setValue(out);
    int i ;
    for ( i = 1 ; i< inputList().size() ; i++);
    {
        if  ( inputList()[i]->value() == out )
            out = 0 ;
        else
            out = 1 ;
    }
    outputNode()->setValue(out);*/
    if(in1()->value() == Pin::False && in2()->value() == Pin::False)
    {
        out_logic = Pin::False;
    }
    else if(in1()->value() == Pin::True && in2()->value() == Pin::False)
    {
        out_logic = Pin::True;
    }
    else if(in1()->value() == Pin::False && in2()->value() == Pin::True)
    {
        out_logic = Pin::True;
    }
    else if(in1()->value() == Pin::True && in2()->value() == Pin::True)
    {
        out_logic = Pin::False;
    }
    else
    {
        out_logic = Pin::Undefined;
    }
    qDebug() << "calculate XOR called";
    qDebug() << out_logic;
    emit outputChanged(out_logic);
}

QString XorGate::imageUrl() const
{
    return QString(":/gates/xor");
}

void XorGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Gate::paint(painter, option, widget);
    QPainterPath path;
    path.arcMoveTo(QRect(-18,-5,25,60), -50);
    path.arcTo(QRect(-19,-2,60,50), -106.25, 93.75);
    path.arcTo(QRect(-19,4,60,50), 12.5, 93.75);
    path.arcTo(QRect(-18,-5,25,60), 43.75, -93.75);
    path.arcMoveTo(QRect(-22,-5,25,60), -46.875);
    path.arcTo(QRect(-22,-5,25,60), -46.875, 84.375);
    painter->drawPath(path);
}

// ===================== XnorGate ===================

XnorGate::XnorGate()
    : Gate(Component::XnorGate)
{
    setMetaTypeId(qRegisterMetaType<XnorGate>("XnorGate"));
    setToolTip("Xnor Gate");
}

XnorGate::XnorGate(const XnorGate &g)
    : Gate(g.componentType())
{
}

void XnorGate::calcOutput()
{
    Pin::Value out_logic;
    /*outputNode()->setValue(out);
    int i ;
    for( i = 1 ; i< inputList().size() ; i++)
    {
        if( inputList()[i]->value() == out )
            out = 0 ;
        else
            out = 1 ;
    }
    outputNode()->setValue(!out);*/
    if(in1()->value() == Pin::False && in2()->value() == Pin::False)
    {
        out_logic = Pin::False;
    }
    else if(in1()->value() == Pin::True && in2()->value() == Pin::False)
    {
        out_logic = Pin::True;
    }
    else if(in1()->value() == Pin::False && in2()->value() == Pin::True)
    {
        out_logic = Pin::True;
    }
    else if(in1()->value() == Pin::True && in2()->value() == Pin::True)
    {
        out_logic = Pin::False;
    }
    else
    {
        out_logic = Pin::Undefined;
    }
    if(out_logic == Pin::False)
    {
        out_logic = Pin::True;
    }
    else if(out_logic == Pin::True)
    {
        out_logic = Pin::False;
    }
    else
    {
        out_logic = Pin::Undefined;
    }
    qDebug() << "calculate XNOR called";
    qDebug() << out_logic;
    emit outputChanged(out_logic);
}

QString XnorGate::imageUrl() const
{
    return QString(":/gates/xnor");
}

void XnorGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Gate::paint(painter, option, widget);
    QPainterPath path;
    path.arcMoveTo(QRect(-18,-5,25,60), -50);
    path.arcTo(QRect(-24,-2,60,50), -96.875, 87.5);
    path.arcTo(QRect(36,25,5,5), 180, -360);
    path.arcTo(QRect(-24,4,60,50), 12.5, 81.25);
    path.arcTo(QRect(-18,-5,25,60), 43.75, -93.75);
    path.arcMoveTo(QRect(-22,-5,25,60), -46.875);
    path.arcTo(QRect(-22,-5,25,60), -46.875, 84.375);
    painter->drawPath(path);
}

} // namespace Logicsim
