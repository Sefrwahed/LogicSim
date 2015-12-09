#ifndef GATE_H
#define GATE_H

// Qt includes

#include <QCoreApplication>

// Local includes

#include "logicsim_global.h"
#include "node.h"
#include "gateparts.h"
#include "graphicgate.h"

namespace Logicsim
{

// ===================== AndGate ================

class AndGate: public GraphicGate
{
public:
    AndGate();
    AndGate(const AndGate& g);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void calcOutput();
    QString imageUrl() const;
};

// ===================== OrGate =================

class OrGate: public  GraphicGate
{
public:
    OrGate();
    OrGate(const OrGate& g);

    void calcOutput();
    QString imageUrl() const;
};

// ===================== NotGate ================

class NotGate: public GraphicGate
{
public:
    NotGate();
    NotGate(const NotGate& g);

    void calcOutput();
    QString imageUrl() const;
    void paint();
};

} // namespace Logicsim

#endif // GATE_H