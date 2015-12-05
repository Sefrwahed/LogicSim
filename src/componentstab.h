#ifndef COMPONENTSTAB_H
#define COMPONENTSTAB_H

#include <QTableWidget>
#include <QDebug>
#include <QMimeData>
#include <QHeaderView>

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

}

#endif // COMPONENTSTAB_H
