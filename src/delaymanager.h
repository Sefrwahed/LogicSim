#ifndef DELAYMANAGER_H
#define DELAYMANAGER_H

#include "component.h"

namespace Logicsim
{

class delaymanager
{
public:
    delaymanager();
    int gateDelay (Component::Type t);

private:
    int andDelay,orDelay;
};

}
#endif // DELAYMANAGER_H
