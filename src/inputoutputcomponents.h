#ifndef INPUTOUTPUTCOMPONENTS
#define INPUTOUTPUTCOMPONENTS

// Qt includes

#include <QtWidgets>

// Local includes

#include "node.h"
#include "inouparts.h"
#include "pin.h"
#include "component.h"
#include "logicsim_global.h"

namespace Logicsim
{
class InputComponent : public Component
{
public:
    InputComponent();
    InputComponent(const InputComponent& g);
    ~InputComponent();

    QRectF boundingRect() const;
    QString imageUrl() const;

    void updateConnection();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    Node * bodyNode();
    void setBodyNode(Node *n);

private:
    Node *pnode;
    Pin* m_pin;
};

// ==============================================

class OutputComponent : public Component
{ 
public:
    OutputComponent();
    OutputComponent(const OutputComponent& g);
    ~OutputComponent();

    QRectF boundingRect() const;
    QString imageUrl() const;

    void updateConnection();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    Node * bodyNode();
    void setBodyNode(Node *n);

private:
    Node *pnode;
    Pin* m_pin;
};

}

#endif // INPUTOUTPUTCOMPONENTS

