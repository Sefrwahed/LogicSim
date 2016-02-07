#include "simulator.h"

Simulator Simulator::getInstance()
{
    if(instance == null) instance = new Simulator();
            return instance;
}

Simulator::Simulator()
{

}

