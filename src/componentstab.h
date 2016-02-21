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
#include "inputoutputcomponents.h"

namespace Logicsim
{

class ComponentsTab : public QTableWidget
{
    Q_OBJECT

public:
    ComponentsTab(QWidget* parent = 0);
    ~ComponentsTab();

    QList<Component *> &componentsCollection();

protected:
    QMimeData* mimeData(const QList<QTableWidgetItem *> items) const;

private:
    QList<QTableWidgetItem*> m_items;
    QList<Component*> m_componenets;
};

} // namespace Logicsim

#endif // COMPONENTSTAB_H
