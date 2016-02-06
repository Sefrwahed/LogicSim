#ifndef WORKSPACETAB_H
#define WORKSPACETAB_H

#include <QTableWidget>
#include <QDebug>

namespace Logicsim
{

class WorkspaceTab : public QTableWidget
{
    Q_OBJECT

public:
    WorkspaceTab(QWidget* parent = 0);
    ~WorkspaceTab();
};

}
#endif // WORKSPACETAB_H
