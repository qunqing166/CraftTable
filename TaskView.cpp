#include "FileManagement.h"
#include "TaskView.h"
#include "TaskViewItem.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

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

    // for(int i = 0; i < 10; i++)
    // {
    //     QListWidgetItem *item = new QListWidgetItem(this);
    //     TaskInfo info;
    //     info.SetInfo("nmslughfsiodhfoasjspoajkjshdfloajsdlosihjfoisa" + QString::number(i));
    //     TaskViewItem *vItem = new TaskViewItem(info, item, this);
    //     this->addItem(item);
    //     this->setItemWidget(item, vItem);

    //     connect(vItem, &TaskViewItem::Delete, this, &TaskView::OnItemRemove);
    //     connect(vItem, &TaskViewItem::Complete, this, &TaskView::OnItemRemove);
    //     connect(vItem, &TaskViewItem::Edit, this, [&](TaskViewItem* item){emit this->Edit(item);});
    // }
    Load();

    connect(animaRmvItemHeight, &QPropertyAnimation::valueChanged, this, [&](){
        removedItem->setSizeHint(QSize(200, rmvItemHeight));
    });
    connect(animaRmvItemHeight, &QPropertyAnimation::finished, this, [&](){
        delete removedItem;
    });

}

TaskView::~TaskView()
{
    Save();
}

void TaskView::AddTask(TaskInfo info)
{
    QListWidgetItem *item = new QListWidgetItem(this);
    info.SetInfo(info.GetInfo());
    TaskViewItem *vItem = new TaskViewItem(info, item, this);
    this->addItem(item);
    this->setItemWidget(item, vItem);

    connect(vItem, &TaskViewItem::Delete, this, &TaskView::OnItemRemove);
    connect(vItem, &TaskViewItem::Complete, this, &TaskView::OnItemRemove);
    connect(vItem, &TaskViewItem::Edit, this, [&](TaskViewItem* item){emit this->Edit(item);});
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

void TaskView::Load()
{
    QJsonObject obj = FileManagement::Instance()->LoadJsonFile();

    int num = obj["num"].toInt();
    QJsonArray arr = obj["data"].toArray();
    for(int i = 0; i < arr.count(); ++i)
    {
        this->AddTask(TaskInfo::FromJson(arr[i].toObject()));
    }
}

void TaskView::Save()
{
    QJsonObject obj;
    obj.insert("num", this->count());

    QJsonArray array;
    for(int i = 0; i < this->count(); i++)
    {
        QListWidgetItem *item = this->item(i);
        TaskViewItem *itemWidget = dynamic_cast<TaskViewItem*>(this->itemWidget(item));
        array.append(itemWidget->GetTaskInfo().ToJson());
    }

    obj.insert("data", array);

    FileManagement::Instance()->SaveJsonFile(obj);

    qDebug() << obj;
}

