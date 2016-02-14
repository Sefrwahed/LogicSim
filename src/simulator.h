#ifndef SIMULATOR_H
#define SIMULATOR_H

// Qt includes

#include <QList>

// Local includes

#include "gate.h"
#include "inputoutputcomponents.h"
#include "component.h"

namespace Logicsim
{
class Simulator
{
public:
    static Simulator * getInstance();
    void simulate(QList<Component *> list);
    QList<Gate *>GatesFromComponets(QList<Component *> list);
private:
    static Simulator * instance;
    Simulator();

};
} // namespace Logicsim
#endif // SIMULATOR_H
