#ifndef CONNECTIONLINE_H
#define CONNECTIONLINE_H

// Qt includes

#include <QGraphicsLineItem>

// Local includes

#include "pin.h"

namespace Logicsim
{

class Pin;

class ConnectionLine : public QGraphicsLineItem
{
public:
    ConnectionLine(const QLineF &line, QGraphicsItem* parent=0);
    ~ConnectionLine();

    Pin* output() const;
    Pin* input() const;

private:
    Pin* m_out;
    Pin* m_in;
};

} // namespace Logicsim

#endif // CONNECTIONLINE_H
