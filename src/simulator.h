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
class Simulator : public QObject
{
    Q_OBJECT
public:
    static Simulator * getInstance();

    QList<Gate *>GatesFromComponets(QList<Component *> list);
private:
    static Simulator * instance;
    Simulator();
public Q_SLOTS:
    void simulate(OutputComponent *);

};
} // namespace Logicsim
#endif // SIMULATOR_H
