#include "gates.h"

// Qt includes

#include <QDebug>
#include <QPainter>

namespace Logicsim
{

// ===================== AndGate ===================

AndGate::AndGate()
    : GraphicGate(AbstractGate::AndGate)
{
    setMetaTypeId(qRegisterMetaType<AndGate>("AndGate"));
}

AndGate::AndGate(const AndGate &g)
    : GraphicGate(g.gateType())
{
}

QRectF AndGate::boundingRect() const
{
    return QRectF(0,0,40,50);
}

void AndGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
//    painter->drawRoundedRect(QRect(0,0,40,50),5,10);
    painter->drawLine(0,0,0,50);
    painter->drawLine(0,0,20,0);
    painter->drawLine(0,50,20,50);
    painter->drawArc(QRect(0,0,40,50), -1400, 3000);
}

void AndGate::calcOutput()
{
    bool out = true;
    foreach (Node * n, inputList())
    {
        out &= n->value();
    }

    outputNode()->setValue(out);
}

QString AndGate::imageUrl() const
{
    return QString(":/gates/and");
}

// ===================== OrGate ===================

OrGate::OrGate()
    : GraphicGate(AbstractGate::OrGate)
{
    setMetaTypeId(qRegisterMetaType<OrGate>("OrGate"));
}

OrGate::OrGate(const OrGate &g)
    : GraphicGate(g.gateType())
{
}

void OrGate::calcOutput()
{
    bool out = false;
    foreach (Node * n, inputList())
    {
        out |= n->value();
    }

    outputNode()->setValue(out);
}

QString OrGate::imageUrl() const
{
    return QString(":/gates/or");
}

// ===================== NotGate ===================

NotGate::NotGate()
    : GraphicGate(AbstractGate::NotGate)
{
    setMaxInput(1);
    setMetaTypeId(qRegisterMetaType<NotGate>("NotGate"));
}

NotGate::NotGate(const NotGate &g)
    : GraphicGate(g.gateType())
{
}

void NotGate::calcOutput()
{
    bool out = inputList()[0]->value();
    outputNode()->setValue(!out);
}

QString NotGate::imageUrl() const
{
    return QString(":/gates/not");
}

} // namespace Logicsim
