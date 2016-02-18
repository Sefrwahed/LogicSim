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
public slots:
    void calcOutput() override;
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
public slots:
    void calcOutput() override;
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
public slots:
    void calcOutput() override;

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

    // QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


//    void calcOutput();
    QString imageUrl() const;

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
public slots:
    void calcOutput() override;
};

// ===================== NorGate ================

class NorGate: public Gate
{
    Q_OBJECT
public:
    NorGate();
    NorGate(const NorGate& g);

//    void calcOutput();
    QString imageUrl() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
public slots:
    void calcOutput() override;
};

// ===================== XorGate ================

class XorGate: public Gate
{
    Q_OBJECT
public:
    XorGate();
    XorGate(const XorGate& g);

//    void calcOutput();
    QString imageUrl() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
public slots:
    void calcOutput() override;
};

// ===================== XnorGate ================

class XnorGate: public Gate
{
    Q_OBJECT
public:
    XnorGate();
    XnorGate(const XnorGate& g);

//    void calcOutput();
    QString imageUrl() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
    { Gate::mouseMoveEvent(e); }
public slots:
    void calcOutput() override;
};

} // namespace Logicsim

#endif // GATE_H
