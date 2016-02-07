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
    Node(bool c);
    void setName(QString n);
    void setValue(bool v);
    void setCalc(bool c);
    QString name();
    bool value();
    bool isCalc();


private:
    bool m_value;
    QString m_name;
    bool calc;
};

} // namespace Logics

#endif // NODE_H
