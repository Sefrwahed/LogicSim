#include "simulator.h"
namespace Logicsim
{
Simulator::Simulator()
{

}

Simulator* Simulator::instance = 0;
Simulator* Simulator::getInstance()
{
    if(instance == 0) instance = new Simulator();
    return instance;
}

/*
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

} */


void Simulator::simulate(OutputComponent*)
{

}

} // namespace Logicsim
