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

private:
    void closeEvent(QCloseEvent * e);

public Q_SLOTS:
    Canvas *newFile();
    void closeTab(int tabIndex);
    void changeManager(int index);
    void tabChanged(int index);
    void tabAboutToBeClosed(int index);
    void setActiveTab(int index);
    void appAboutToQuit();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actiondelays_triggered();

private slots:
    void getDelays(int delay);
    
signals:
    void delaysForCanvas(int delay);



Q_SIGNALS:
    void notLastTabClosed(int index);
    void actiondelaysTriggered();

private:
    Ui::MainWindow *ui;

    class Private;
    Private* const d;
};

} // namespace Logicsim

#endif // MAINWINDOW_H
