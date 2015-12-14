#ifndef NODE_H
#define NODE_H

// Qt includes
#include <QCoreApplication>

namespace Logicsim
{

class Node
{
public:
    Node();

    void setName(QString n);
    void setValue(bool v);
    QString name();
    bool value();

private:
    bool m_value;
    QString m_name;
};

} // namespace Logics

#endif // NODE_H
