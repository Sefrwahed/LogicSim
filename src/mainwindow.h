#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt includes
#include <QMainWindow>
#include <QGraphicsSceneDragDropEvent>
#include <QLabel>

// Local includes
#include "componentstab.h"
#include "workspacetab.h"

namespace Ui {
class MainWindow;
}

namespace Logicsim
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initComponentsTab();
    void initWorkspaceTab();
    void setMainFrameDisabled(bool disabled);

public Q_SLOTS:
    void newFile();
    void closeTab(int tabIndex);
    void changeManager(int index);

Q_SIGNALS:
    void notLastTabClosed(int index);

private:
    Ui::MainWindow *ui;

    class Private;
    Private* const d;
};

} // namespace Logicsim

#endif // MAINWINDOW_H
