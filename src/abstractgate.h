#ifndef ABSTRACTGATE_H
#define ABSTRACTGATE_H

// Qt includes

#include <QObject>

// Local includes

#include "node.h"

namespace Logicsim
{

class AbstractGate : public QObject
{
public:
    enum Type
    {
        AndGate = 0,
        OrGate,
        NotGate,
        NandGate,
        NorGate,
        XorGate,
        XnorGate
    };

public:
    ~AbstractGate();

    qint16 maxInput();
    Node* outputNode();
    void setInput(QList<Node*>& n);
    Type gateType() const;

    virtual void calcOutput() = 0;
    virtual QString imageUrl() const = 0;

    int metaTypeId() const;

protected:
    AbstractGate(Type t);

    void setMaxInput(qint16 mi);
    QList<Node*> inputList() const;

    void setMetaTypeId(int t);

private:
    class Private;
    Private* const d;
};

} // namespace Logicsim

#endif // ABSTRACTGATE_H
