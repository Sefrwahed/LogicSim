#include "simulator.h"
namespace Logicsim
{
Simulator* Simulator::instance = 0;
Simulator* Simulator::getInstance()
{
    if(instance == 0) instance = new Simulator();
    return instance;
}

void Simulator::simulate(QList<Component *> list)
{
    QList<Gate *> g = GatesFromComponets(list);
    int t = g.count();
    while(t > 0){
    foreach(Gate* p, g) {
        bool c = 1;
        foreach (Node * n, p->inputList()){
            c = c && n->isCalc();
        }
        if(c)
        {
            p->calcOutput();
        }
    }
    t--;
    }
}

QList<Gate *> Simulator::GatesFromComponets(QList<Component *> list)
{
    QList<Gate *> gates;

    foreach (Component * g, list)
    {
        if(/*g is Gate*/0)
        {
            //gates.append(g);
        }
    }
    return gates;
}


Simulator::Simulator()
{

}

} // namespace Logicsim
