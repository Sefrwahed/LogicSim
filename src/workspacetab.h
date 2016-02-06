#ifndef WORKSPACETAB_H
#define WORKSPACETAB_H

#include <QTableWidget>
#include <QDebug>

#include "canvas.h"
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

    void addCanvas(Canvas *canvas);

public Q_SLOTS:
    void currentCanvas(int index);
    void updateGates();

private:
    class Private;
    Private* const d;
};

}
#endif // WORKSPACETAB_H
