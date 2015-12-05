#include "componentstab.h"

namespace Logicsim
{

const int GATES_TYPES_COUNT = 7;

class ComponentsTab::Private
{
public:
    Private() :
        rows(0),
        columns(0)
    {}
    int rows;
    int columns;
};

ComponentsTab::ComponentsTab(QWidget* parent)
    : QTableWidget(parent), d(new Private)
{
    this->verticalHeader()->setVisible(false);
    this->horizontalHeader()->setVisible(false);

    if(GATES_TYPES_COUNT % 2 != 0)
        this->setRowCount(GATES_TYPES_COUNT/2 + 1);
    else
        this->setRowCount(GATES_TYPES_COUNT/2);

    this->setColumnCount(2);
    this->setShowGrid(false);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->setDragEnabled(true);

    QPixmap gatePixmap[GATES_TYPES_COUNT];
    QLabel* gateItem[GATES_TYPES_COUNT];
    gatePixmap[0] = QPixmap(":/gates/and");
    gatePixmap[1] = QPixmap(":/gates/nand");
    gatePixmap[2] = QPixmap(":/gates/nor");
    gatePixmap[3] = QPixmap(":/gates/not");
    gatePixmap[4] = QPixmap(":/gates/or");
    gatePixmap[5] = QPixmap(":/gates/xnor");
    gatePixmap[6] = QPixmap(":/gates/xor");

    for(int i = 0; i < GATES_TYPES_COUNT; i++)
    {
        gateItem[i] = new QLabel();
        gateItem[i]->setPixmap(gatePixmap[i]);
        gateItem[i]->setObjectName("gate");
    }
    for(int item_no = 0; item_no < GATES_TYPES_COUNT; item_no += 2)
    {
        this->setCellWidget(item_no/2, 0, gateItem[item_no]);
    }
    for(int item_no = 1; item_no < GATES_TYPES_COUNT; item_no += 2)
    {
        this->setCellWidget(item_no/2, 1, gateItem[item_no]);
    }
    this->resizeColumnsToContents();
    this->resizeRowsToContents();
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

ComponentsTab::~ComponentsTab()
{
    delete d;
}

QMimeData* ComponentsTab::mimeData(const QList<QTableWidgetItem *> items) const
{
    QMimeData *data = QTableWidget::mimeData(items);
    data->setObjectName("gate");

    return data;
}
}
