#include "TaskView.h"
#include "TaskViewItem.h"

TaskView::TaskView(QWidget *parent):QListWidget(parent)
{
    animaRmvItemHeight = new QPropertyAnimation(this, "RmvItemHeight", this);
    animaRmvItemHeight->setStartValue(60);
    animaRmvItemHeight->setEndValue(0);

    this->setDragEnabled(true);        // 允许拖拽
    this->setAcceptDrops(true);        // 允许放置
    this->setSelectionMode(QAbstractItemView::SingleSelection); // 单选模式
    this->setDefaultDropAction(Qt::MoveAction); // 默认拖拽操作为移动

    this->setStyleSheet(R"(
            background-color:white;
    )");
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i = 0; i < 10; i++)
    {
        QListWidgetItem *item = new QListWidgetItem(this);
        TaskInfo info;
        info.SetInfo("nmslughfsiodhfoasjspoajkjshdfloajsdlosihjfoisa" + QString::number(i));
        TaskViewItem *vItem = new TaskViewItem(info, item, this);
        this->addItem(item);
        this->setItemWidget(item, vItem);

        connect(vItem, &TaskViewItem::Delete, this, &TaskView::OnItemRemove);
        connect(vItem, &TaskViewItem::Complete, this, &TaskView::OnItemRemove);
    }
    connect(animaRmvItemHeight, &QPropertyAnimation::valueChanged, this, [&](){
        removedItem->setSizeHint(QSize(200, rmvItemHeight));
    });
    connect(animaRmvItemHeight, &QPropertyAnimation::finished, this, [&](){
        delete removedItem;
    });
}

void TaskView::OnItemRemove(QListWidgetItem *item)
{
    removedItem = item;
    this->itemWidget(item)->disconnect();
    this->itemWidget(item)->deleteLater();
    this->removeItemWidget(item);
    animaRmvItemHeight->setStartValue(removedItem->sizeHint().height());
    animaRmvItemHeight->start();
}
