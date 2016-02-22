#ifndef DELAYSDIALOG_H
#define DELAYSDIALOG_H

#include <QDialog>

namespace Ui {
class delaysDialog;
}

class delaysDialog : public QDialog
{
    Q_OBJECT

public:
    explicit delaysDialog(QWidget *parent = 0);
    ~delaysDialog();

private slots:
    void on_spinBox_and_valueChanged(int arg1);

    void on_buttonBox_accepted();

private:
    Ui::delaysDialog *ui;
    qint32 andDelay,orDelay;

signals:
    void sendDelays(int delay1);
};

#endif // DELAYSDIALOG_H
