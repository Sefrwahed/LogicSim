#include "delaysdialog.h"
#include "ui_delaysdialog.h"

delaysDialog::delaysDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delaysDialog)
{
    ui->setupUi(this);
    andDelay = 0;
    orDelay = 0;

    ui->spinBox_and->setRange(0,1000000);
    ui->spinBox_and->setSingleStep(100);

    ui->spinBox_or->setRange(0,1000000);
    ui->spinBox_or->setSingleStep(100);
}

delaysDialog::~delaysDialog()
{
    delete ui;
}

void delaysDialog::on_spinBox_and_valueChanged(int arg1)
{
    andDelay = arg1;
}

void delaysDialog::on_buttonBox_accepted()
{
    emit sendDelays(andDelay);
}
