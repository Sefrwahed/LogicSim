#ifndef COMPONENTSTAB_H
#define COMPONENTSTAB_H

// Qt includes
#include <QTableWidget>
#include <QDebug>
#include <QMimeData>
#include <QHeaderView>

// Local includes

#include "logicsim_global.h"
#include "gates.h"

namespace Logicsim
{

class ComponentsTab : public QTableWidget
{
    Q_OBJECT

public:
    ComponentsTab(QWidget* parent = 0);
    ~ComponentsTab();

protected:
    QMimeData* mimeData(const QList<QTableWidgetItem *> items) const;

private:
    QList<QTableWidgetItem*> m_items;
    QList<Gate*> m_gates;
};

} // namespace Logicsim

#endif // COMPONENTSTAB_H
