#ifndef COMPONENTSTAB_H
#define COMPONENTSTAB_H

#include <QTableWidget>
#include <QDebug>
#include <QMimeData>
#include <QLabel>
#include <QHeaderView>

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
    class Private;
    Private* const d;
};

}

#endif // COMPONENTSTAB_H
