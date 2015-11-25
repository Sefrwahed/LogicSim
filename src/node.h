#include <string>
using namespace std;

#ifndef NODE_H
#define NODE_H
namespace Logicsim {

class Node
{
private:
    bool value;
    string name;
public:
    Node();
    ~Node();
    void setName(string n);
    void setValue(bool v);
    string getName();
    bool getValue();

};
}
#endif // NODE_H
