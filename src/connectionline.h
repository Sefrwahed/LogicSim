#ifndef CONNECTIONLINE_H
#define CONNECTIONLINE_H

// Qt includes

#include <QGraphicsLineItem>
#include <QObject>

// Local includes

#include "pin.h"

namespace Logicsim
{

class Pin;

class ConnectionLine : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    ConnectionLine(const QLineF &line, QGraphicsItem* parent=0);
    ~ConnectionLine();

    Pin* output() const;
    Pin* input() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    Pin* m_out;
    Pin* m_in;
};

} // namespace Logicsim

#endif // CONNECTIONLINE_H
