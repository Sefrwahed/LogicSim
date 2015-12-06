#include "componentstab.h"

namespace Logicsim
{

const int GATES_TYPES_COUNT = 7;

ComponentsTab::ComponentsTab(QWidget* parent)
    : QTableWidget(parent)
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

    gateItem[0] = new QTableWidgetItem(Gate::AndGate);
    gateItem[1] = new QTableWidgetItem(Gate::NandGate);
    gateItem[2] = new QTableWidgetItem(Gate::NorGate);
    gateItem[3] = new QTableWidgetItem(Gate::NotGate);
    gateItem[4] = new QTableWidgetItem(Gate::OrGate);
    gateItem[5] = new QTableWidgetItem(Gate::XnorGate);
    gateItem[6] = new QTableWidgetItem(Gate::XorGate);

    for(int i = 0; i < GATES_TYPES_COUNT; i++)
    {
        gateItem[i]->setData(Qt::DecorationRole, gatePixmap[i]
                           .scaled(120, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    for(int item_no = 0; item_no < GATES_TYPES_COUNT; item_no += 2)
    {
        setItem(item_no/2, 0, gateItem[item_no]);
    }
    for(int item_no = 1; item_no < GATES_TYPES_COUNT; item_no += 2)
    {
        setItem(item_no/2, 1, gateItem[item_no]);
    }
    if(GATES_TYPES_COUNT % 2 != 0)
    {
        //create a transperent pixmap and set it to the empty item
        QPixmap pixmap(16, 16);
        pixmap.fill(QColor("white"));
        QTableWidgetItem *emptySlot = new QTableWidgetItem();
        emptySlot->setData(Qt::DecorationRole, pixmap);
        //make the item selectable which makes the pixmap not selectable
        emptySlot->setFlags(Qt::ItemIsSelectable);
        setItem((GATES_TYPES_COUNT)/2, 1,emptySlot);
    }
    resizeColumnsToContents();
    resizeRowsToContents();
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

QMimeData* ComponentsTab::mimeData(const QList<QTableWidgetItem *> items) const
{
    QMimeData *data = QTableWidget::mimeData(items);
    data->setProperty("type", items.at(0)->type());
    data->setProperty("acceptable", true);
    return data;
}

}