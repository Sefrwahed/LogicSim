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
    void addGateToWorkspace(int index);
    void removeGateFromWorkspace(int index);
    void selectedFromCanvas(int index);

Q_SIGNALS:
    void gateSelectedFromWorkspace(int index);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    class Private;
    Private* const d;
};

}
#endif // WORKSPACETAB_H
