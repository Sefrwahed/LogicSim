#include "delaysdialog.h"
#include "ui_delaysdialog.h"


namespace Logicsim
{
DelaysDialog* DelaysDialog::m_instance = 0;

DelaysDialog::DelaysDialog() :
    QDialog(0),
    ui(new Ui::delaysDialog)
{
    m_delays[Component::AndGate] = 800;
    m_delays[Component::OrGate] = 15;
    m_delays[Component::NotGate] = 0;
    m_delays[Component::XorGate] = 0;
    m_delays[Component::XnorGate] = 0;
    m_delays[Component::NandGate] = 0;
    m_delays[Component::NorGate] = 0;

    ui->setupUi(this);

    ui->spinBox_and->setRange(0,1000000);
    ui->spinBox_and->setSingleStep(100);
    ui->spinBox_and->setValue(m_delays[Component::AndGate]);

    ui->spinBox_or->setRange(0,1000000);
    ui->spinBox_or->setSingleStep(100);
    ui->spinBox_or->setValue(m_delays[Component::OrGate]);
}

DelaysDialog *DelaysDialog::instance()
{
    if(m_instance == 0)
        m_instance = new DelaysDialog();

    return m_instance;
}

DelaysDialog::~DelaysDialog()
{
    delete ui;
}

int DelaysDialog::gateDelay(Component::Type t)
{
    return m_delays[t];
}

void DelaysDialog::showDialog()
{
    this->exec();
}

void DelaysDialog::on_spinBox_and_valueChanged(int arg1)
{

}

void DelaysDialog::on_buttonBox_accepted()
{

}

void DelaysDialog::on_spinBox_or_valueChanged(int arg1)
{

}
}
