#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsSceneDragDropEvent>
#include <QLabel>

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

public Q_SLOTS:
    void newFile();
    void closeTab(int tabIndex);

private:
    Ui::MainWindow *ui;

    class Private;
    Private* const d;
};

} // namespace Logicsim

#endif // MAINWINDOW_H
