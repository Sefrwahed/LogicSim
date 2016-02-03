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

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { GraphicGate::mouseMoveEvent(e); }
};

// ===================== OrGate =================

class OrGate: public  GraphicGate
{
public:
    OrGate();
    OrGate(const OrGate& g);

    void calcOutput();
    QString imageUrl() const;

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { GraphicGate::mouseMoveEvent(e); }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

// ===================== NotGate ================

class NotGate: public GraphicGate
{
public:
    NotGate();
    NotGate(const NotGate& g);

    void calcOutput();
    QString imageUrl() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { GraphicGate::mouseMoveEvent(e); }
};

// ===================== NandGate ================

class NandGate: public GraphicGate
{
public:
    NandGate();
    NandGate(const NandGate& g);

    // QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    void calcOutput();
    QString imageUrl() const;

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { GraphicGate::mouseMoveEvent(e); }
};
// ===================== NorGate ================

class NorGate: public GraphicGate
{
public:
    NorGate();
    NorGate(const NorGate& g);

    void calcOutput();
    QString imageUrl() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { GraphicGate::mouseMoveEvent(e); }
};
// ===================== XorGate ================

class XorGate: public GraphicGate
{
public:
    XorGate();
    XorGate(const XorGate& g);

    void calcOutput();
    QString imageUrl() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { GraphicGate::mouseMoveEvent(e); }
};


// ===================== XnorGate ================

class XnorGate: public GraphicGate
{
public:
    XnorGate();
    XnorGate(const XnorGate& g);

    void calcOutput();
    QString imageUrl() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { GraphicGate::mouseMoveEvent(e); }
};


} // namespace Logicsim

#endif // GATE_H