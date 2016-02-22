#include "delaymanager.h"


namespace Logicsim
{
delaymanager::delaymanager()
{

}

int delaymanager::gateDelay(Component::Type t)
{
    switch (t) {
    case 0:
        return andDelay;
        break;
    case 1:
        return orDelay;
        break;
    default:
        return 0;
        break;
    }
}
}
