#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt includes
#include <QMainWindow>
#include <QGraphicsSceneDragDropEvent>
#include <QLabel>

// Local includes
#include "componentstab.h"
#include "workspacetab.h"
#include "canvas.h"

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
    Canvas *newFile();
    void closeTab(int tabIndex);
    void changeManager(int index);
    void tabChanged(int index);

Q_SIGNALS:
    void notLastTabClosed(int index);

private slots:
    void on_actionSave_triggered();
    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;

    class Private;
    Private* const d;
};

} // namespace Logicsim

#endif // MAINWINDOW_H
