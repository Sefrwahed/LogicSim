#include "simulator.h"
namespace Logicsim
{
Simulator* Simulator::instance = 0;
Simulator* Simulator::getInstance()
{
    if(instance == 0) instance = new Simulator();
            return instance;
}

Simulator::Simulator()
{

}

} // namespace Logicsim
