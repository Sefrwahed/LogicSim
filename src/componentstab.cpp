#include "componentstab.h"

namespace Logicsim
{

const int GATES_TYPES_COUNT = 7;

class ComponentsTab::Private
{
public:
    Private()
    {}
};

ComponentsTab::ComponentsTab(QWidget* parent)
    : QTableWidget(parent), d(new Private)
{
    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(false);

    if(GATES_TYPES_COUNT % 2 != 0)
        setRowCount(GATES_TYPES_COUNT/2 + 1);
    else
        setRowCount(GATES_TYPES_COUNT/2);

    setColumnCount(2);
    setShowGrid(false);
    setDragEnabled(true);

    QPixmap gatePixmap[GATES_TYPES_COUNT];
    gatePixmap[0] = QPixmap(":/gates/and");
    gatePixmap[1] = QPixmap(":/gates/nand");
    gatePixmap[2] = QPixmap(":/gates/nor");
    gatePixmap[3] = QPixmap(":/gates/not");
    gatePixmap[4] = QPixmap(":/gates/or");
    gatePixmap[5] = QPixmap(":/gates/xnor");
    gatePixmap[6] = QPixmap(":/gates/xor");

    QTableWidgetItem *gateItem[GATES_TYPES_COUNT];

    gateItem[0] = new QTableWidgetItem(AndGate);
    gateItem[1] = new QTableWidgetItem(NandGate);
    gateItem[2] = new QTableWidgetItem(NorGate);
    gateItem[3] = new QTableWidgetItem(NotGate);
    gateItem[4] = new QTableWidgetItem(OrGate);
    gateItem[5] = new QTableWidgetItem(XnorGate);
    gateItem[6] = new QTableWidgetItem(XorGate);

    for(int i = 0; i < GATES_TYPES_COUNT; i++)
    {
        gateItem[i]->setData(Qt::DecorationRole, gatePixmap[i]
                           .scaled(120, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

 /*   //names to detect which item was dragged
    gateItem[0]->setData(Qt::UserRole, AndGate);
    gateItem[1]->setData(Qt::UserRole, NandGate);
    gateItem[2]->settData(Qt::UserRole, NorGate);
    gateItem[3]->setData(Qt::UserRole, NotGate);
    gateItem[4]->setData(Qt::UserRole, OrGate);
    gateItem[5]->setData(Qt::UserRole, XnorGate);
    gateItem[6]->setData(Qt::UserRole, XorGate);*/

    for(int item_no = 0; item_no < GATES_TYPES_COUNT; item_no += 2)
    {
        setItem(item_no/2, 0, gateItem[item_no]);
    }
    for(int item_no = 1; item_no < GATES_TYPES_COUNT; item_no += 2)
    {
        setItem(item_no/2, 1, gateItem[item_no]);
    }
    resizeColumnsToContents();
    resizeRowsToContents();
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

QMimeData* ComponentsTab::mimeData(const QList<QTableWidgetItem *> items) const
{
    QMimeData *data = QTableWidget::mimeData(items);
    data->setProperty("type", items.at(0)->type());
    return data;
}

ComponentsTab::~ComponentsTab()
{
    delete d;
}

}
