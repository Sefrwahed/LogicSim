#ifndef WORKSPACETAB_H
#define WORKSPACETAB_H

#include <QTableWidget>
#include <QDebug>
#include <QHeaderView>
#include <QKeyEvent>

#include "canvasmanager.h"
#include "graphicgate.h"

namespace Logicsim
{

class WorkspaceTab : public QTableWidget
{
    Q_OBJECT

public:
    WorkspaceTab(QWidget* parent = 0);
    ~WorkspaceTab();

    void setManager(CanvasManager *canvasManager);

public Q_SLOTS:
    void updateGates();
    void selectedFromCanvas(int index);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    class Private;
    Private* const d;
};

}
#endif // WORKSPACETAB_H
