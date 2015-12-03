#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define GATES_TYPES_NUMBER 7

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtCore>
#include <QtGui>
#include <QGraphicsItem>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initComponentsTab();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    };
#endif // MAINWINDOW_H
