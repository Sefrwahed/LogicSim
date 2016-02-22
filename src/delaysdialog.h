#ifndef DELAYSDIALOG_H
#define DELAYSDIALOG_H

#include <QDialog>
#include "component.h"

namespace Ui {
class delaysDialog;
}

namespace Logicsim {
class DelaysDialog : public QDialog
{
    Q_OBJECT

public:
    static DelaysDialog* instance();
    ~DelaysDialog();

    int gateDelay(Component::Type t);
public Q_SLOTS:
    void showDialog();
private slots:
    void on_spinBox_and_valueChanged(int arg1);
    void on_buttonBox_accepted();
    void on_spinBox_or_valueChanged(int arg1);

private:
    static DelaysDialog* m_instance;
    DelaysDialog();
    Ui::delaysDialog *ui;
    QMap<Component::Type, int> m_delays;

signals:
    void sendDelays(int delay1,int delay2);
};
}
#endif // DELAYSDIALOG_H
