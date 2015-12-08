#ifndef COMPONENTSTAB_H
#define COMPONENTSTAB_H

// Qt includes
#include <QTableWidget>
#include <QDebug>
#include <QMimeData>
#include <QHeaderView>

// Local includes
#include "gate.h"

namespace Logicsim
{

class ComponentsTab : public QTableWidget
{
    Q_OBJECT

public:
    ComponentsTab(QWidget* parent = 0);

protected:
    QMimeData* mimeData(const QList<QTableWidgetItem *> items) const;

};

} // namespace Logicsim

#endif // COMPONENTSTAB_H
