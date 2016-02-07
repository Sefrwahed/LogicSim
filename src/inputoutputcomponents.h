#ifndef INPUTOUTPUTCOMPONENTS
#define INPUTOUTPUTCOMPONENTS

#include "node.h"
#include "inouparts.h"
#include "gateparts.h"
#include "component.h"
#include "logicsim_global.h"
#include <QtWidgets>

namespace Logicsim
{
class InputComponent : public Component
{
public:
    InputComponent(QGraphicsItem *parent = 0);
    InputComponent(const InputComponent& g);
    InputComponent(double xPos, double yPos, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QString imageUrl() const;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};


class OutputComponent : public Component
{
public:
    OutputComponent(QGraphicsItem *parent = 0);
    OutputComponent(const OutputComponent& g);
    OutputComponent(double xPos, double yPos, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QString imageUrl() const;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

}

#endif // INPUTOUTPUTCOMPONENTS

