#include <QtWidgets>
#include "pin.h"
#include "pin.h"
#include "component.h"
#include "inputoutputcomponents.h"

namespace Logicsim {

InputComponent::InputComponent()
    : Component(Component::InputComponent), m_pin(0)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    setMetaTypeId(qRegisterMetaType<InputComponent>("InputComponent"));
    m_pin = new Pin(Pin::Output, this);
    m_pin->setPos(40,10);

    addPins(QList<Pin*>() << m_pin);

    QGraphicsLineItem *Li = new QGraphicsLineItem(QLineF(0,0,10,0), m_pin);
    Li->setPos(-10,5);

    m_pin->updatePinValue(Pin::False);

    setToolTip("Input Component");
}

InputComponent::InputComponent(const InputComponent &g)
    : Component(g.componentType())
{
    Q_UNUSED(g);
}

InputComponent::~InputComponent(){}

QRectF InputComponent::boundingRect() const
{
    return QRectF(0,0,30,30);
}

void InputComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    Component::paint(painter, option, widget);
    if(m_pin->value() == Pin::True)
    {
        painter->setBrush(QColor(0,255,0,180));
    }
    else if(m_pin->value() == Pin::False)
    {
        painter->setBrush(QColor(255,0,0,180));
    }
    else if(m_pin->value() == Pin::Undefined)
    {
        painter->setBrush(QColor(Qt::gray));
    }
    painter->drawEllipse(0,0,30,30);
}

QString InputComponent::imageUrl() const
{
    return QString(":/gates/input");
}

void InputComponent::updateConnection()
{
    m_pin->updateConnectedLine();
}

void InputComponent::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
    m_pin->updateConnectedLine();
//    if(x() - GATE_X_MARGIN < 0)
//    {
//        setPos(GATE_X_MARGIN, y());
//    }
//    else if(x() + boundingRect().right() + GATE_X_MARGIN > CANVAS_WIDTH)
//    {
//        setPos(CANVAS_WIDTH - boundingRect().width() - GATE_X_MARGIN, y());
//    }

//    if(y() < 0)
//    {
//        setPos(x(), GATE_Y_MARGIN);
//    }
//    else if( y()+ boundingRect().bottom() + GATE_Y_MARGIN > CANVAS_HEIGHT)
//    {
//        setPos(x(), CANVAS_HEIGHT - boundingRect().height() - GATE_Y_MARGIN);
//    }
}

void InputComponent::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
qDebug() << "input component dbl click :: updating pin val";
    (m_pin->value() == Pin::True) ? m_pin->updatePinValue(Pin::False) : m_pin->updatePinValue(Pin::True);
    update();

    qDebug()<<"Body clicked";
    qDebug()<<"input changed to : "<<m_pin->value();
}
/*
Node* InputComponent::bodyNode()
{
    return pnode;
}
void InputComponent::setBodyNode(Node *n)
{
    pnode = n;
}
*/
// ==============================================

OutputComponent::OutputComponent()
    : Component(Component::OutputComponent), m_pin(0)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    setMetaTypeId(qRegisterMetaType<OutputComponent>("OutputComponent"));

    m_pin = new Pin(Pin::Input, this);
    m_pin->setPos(-20,10);

    addPins(QList<Pin*>() << m_pin);

    QGraphicsLineItem* Lo = new QGraphicsLineItem(QLineF(0,0,10,0), m_pin);
    Lo->setPos(10,5);

    setToolTip("Output Component");
}

OutputComponent::OutputComponent(const OutputComponent &g): Component(Component::OutputComponent)
{
    Q_UNUSED(g);
}

OutputComponent::~OutputComponent()
{
}

QRectF OutputComponent::boundingRect() const
{
    return QRectF(0,0,30,30);
}

void OutputComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    Component::paint(painter, option, widget);
    painter->setBrush(Qt::SolidPattern);
    if(m_pin != 0)
    {
        if(!m_pin->isConnected() || m_pin->value() == Pin::Undefined)
        {
            painter->setBrush(QColor(Qt::gray));
        }
        else if(m_pin->value() == Pin::True)
        {
            painter->setBrush(QColor(0,255,0,200));
        }
        else if(m_pin->value() == Pin::False)
        {
            painter->setBrush(QColor(255,0,0,200));
        }
    }
    painter->drawRect(0,0,30,30);
}

QString OutputComponent::imageUrl() const
{
    return QString(":/gates/output");
}

void OutputComponent::updateConnection()
{
    m_pin->updateConnectedLine();
}

void OutputComponent::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
    m_pin->updateConnectedLine();
//    if(x() - GATE_X_MARGIN < 0)
//    {
//        setPos(GATE_X_MARGIN, y());
//    }
//    else if(x() + boundingRect().right() + GATE_X_MARGIN > CANVAS_WIDTH)
//    {
//        setPos(CANVAS_WIDTH - boundingRect().width() - GATE_X_MARGIN, y());
//    }

//    if(y() < 0)
//    {
//        setPos(x(), GATE_Y_MARGIN);
//    }
//    else if( y()+ boundingRect().bottom() + GATE_Y_MARGIN > CANVAS_HEIGHT)
//    {
//        setPos(x(), CANVAS_HEIGHT - boundingRect().height() - GATE_Y_MARGIN);
//    }
}

void OutputComponent::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    if(m_pin != 0)
        qDebug()<<"Body clicked"<<m_pin->value();
}

} // namespace Logicsim
