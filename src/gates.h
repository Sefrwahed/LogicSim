#ifndef GATES_H
#define GATES_H

// Qt includes

#include <QCoreApplication>

// Local includes

#include "logicsim_global.h"
#include "pin.h"
#include "gate.h"

namespace Logicsim
{

// ===================== AndGate ================

class AndGate: public Gate
{
    Q_OBJECT
public:
    AndGate();
    AndGate(const AndGate& g);

//    void calcOutput();
    QString imageUrl() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
public Q_SLOTS:
    void calcOutput() ;//;//override;
};

// ===================== OrGate =================

class OrGate: public Gate
{
    Q_OBJECT
public:
    OrGate();
    OrGate(const OrGate& g);

//    void calcOutput();
    QString imageUrl() const;

    QRectF boundingRect() const;


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
public Q_SLOTS:
    void calcOutput();
};

// ===================== NotGate ================

class NotGate: public Gate
{
    Q_OBJECT
public:
    NotGate();
    NotGate(const NotGate& g);

//    void calcOutput();
    QString imageUrl() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
public Q_SLOTS:
    void calcOutput();

private:
    Pin * in2();
};

// ===================== NandGate ================

class NandGate: public Gate
{
    Q_OBJECT
public:
    NandGate();
    NandGate(const NandGate& g);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QString imageUrl() const;

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
public Q_SLOTS:
    void calcOutput();
};

// ===================== NorGate ================

class NorGate: public Gate
{
    Q_OBJECT
public:
    NorGate();
    NorGate(const NorGate& g);

    QString imageUrl() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
public Q_SLOTS:
    void calcOutput();
};

// ===================== XorGate ================

class XorGate: public Gate
{
    Q_OBJECT
public:
    XorGate();
    XorGate(const XorGate& g);

    QString imageUrl() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
public Q_SLOTS:
    void calcOutput();
};

// ===================== XnorGate ================

class XnorGate: public Gate
{
    Q_OBJECT
public:
    XnorGate();
    XnorGate(const XnorGate& g);

    QString imageUrl() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
public Q_SLOTS:
    void calcOutput();
};

} // namespace Logicsim

#endif // GATE_H
