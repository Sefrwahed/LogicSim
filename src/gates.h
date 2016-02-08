#ifndef GATES_H
#define GATES_H

// Qt includes

#include <QCoreApplication>

// Local includes

#include "logicsim_global.h"
#include "node.h"
#include "gateparts.h"
#include "gate.h"

namespace Logicsim
{

// ===================== AndGate ================

class AndGate: public Gate
{
public:
    AndGate();
    AndGate(const AndGate& g);

    void calcOutput();
    QString imageUrl() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
};

// ===================== OrGate =================

class OrGate: public Gate
{
public:
    OrGate();
    OrGate(const OrGate& g);

    void calcOutput();
    QString imageUrl() const;

    QRectF boundingRect() const;


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
};

// ===================== NotGate ================

class NotGate: public Gate
{
public:
    NotGate();
    NotGate(const NotGate& g);

    void calcOutput();
    QString imageUrl() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
};

// ===================== NandGate ================

class NandGate: public Gate
{
public:
    NandGate();
    NandGate(const NandGate& g);

    // QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    void calcOutput();
    QString imageUrl() const;

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
};

// ===================== NorGate ================

class NorGate: public Gate
{
public:
    NorGate();
    NorGate(const NorGate& g);

    void calcOutput();
    QString imageUrl() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
};

// ===================== XorGate ================

class XorGate: public Gate
{
public:
    XorGate();
    XorGate(const XorGate& g);

    void calcOutput();
    QString imageUrl() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
};

// ===================== XnorGate ================

class XnorGate: public Gate
{
public:
    XnorGate();
    XnorGate(const XnorGate& g);

    void calcOutput();
    QString imageUrl() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
};

} // namespace Logicsim

#endif // GATE_H
