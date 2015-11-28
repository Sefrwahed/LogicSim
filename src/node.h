#ifndef NODE_H
#define NODE_H
#include <QCoreApplication>
namespace Logicsim {

class Node
{
private:
    bool value;
    QString name;
public:
    Node();
    void setName(QString n);
    void setValue(bool v);
    QString getName();
    bool getValue();

};
}
#endif // NODE_H
