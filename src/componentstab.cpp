#include "componentstab.h"

namespace Logicsim
{

const int COLUMN_COUNT = 2;

ComponentsTab::ComponentsTab(QWidget* parent)
    : QTableWidget(parent)
{
    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(false);

    setColumnCount(COLUMN_COUNT);
    setShowGrid(false);
    setDragEnabled(true);

    m_gates << new AndGate() << new OrGate() << new NotGate() << new NandGate() << new NorGate()  << new XorGate()   << new XnorGate();
    int gatesCount = 7;

    if(gatesCount % 2 != 0)
    {
        setRowCount(gatesCount/2 + 1);
    }
    else
    {
        setRowCount(gatesCount/2);
    }

    int index = 0;
    foreach (GraphicGate* g, m_gates)
    {
        QTableWidgetItem* item = new QTableWidgetItem(g->gateType());
        item->setData(QTableWidgetItem::UserType, g->metaTypeId());
        item->setData(Qt::DecorationRole, QPixmap(g->imageUrl())
                           .scaled(120, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        if (index % 2 == 0)
        {
            setItem(index/2, 0, item);
        }
        else
        {
             setItem(index/2, 1, item);
        }
        m_items << item;
        index++;
    }

    if(gatesCount % 2 != 0)
    {
        //create a transperent pixmap and set it to the empty item
        QPixmap pixmap(16, 16);
        pixmap.fill(QColor(Qt::transparent));
        QTableWidgetItem *emptySlot = new QTableWidgetItem();
        emptySlot->setData(Qt::DecorationRole, pixmap);
        //make the item selectable which makes the pixmap not selectable
        emptySlot->setFlags(Qt::ItemIsSelectable);
        setItem((gatesCount)/2, 1,emptySlot);
    }

    resizeRowsToContents();
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setMinimumWidth(QPixmap(m_gates[0]->imageUrl()).width()*COLUMN_COUNT);
    setMaximumWidth(minimumWidth());
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

ComponentsTab::~ComponentsTab()
{
    int i = 0;
    foreach (QTableWidgetItem* const item, m_items)
    {
        delete item;
        delete m_gates[i];
        i++;
    }
}

QMimeData* ComponentsTab::mimeData(const QList<QTableWidgetItem *> items) const
{
    QMimeData *data = QTableWidget::mimeData(items);
    data->setProperty("typeId", items.at(0)->data(QTableWidgetItem::UserType));
    data->setProperty("acceptable", true);
    return data;
}

} // namespace Logicsim
