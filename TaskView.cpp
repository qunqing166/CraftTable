#include "FileManagement.h"
#include "TaskView.h"
#include "TaskViewItem.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

TaskView::TaskView(QWidget *parent):QListWidget(parent)
{
    animaRmvItemHeight = new QPropertyAnimation(this, "DeletedItemHeight", this);
    animaRmvItemHeight->setStartValue(60);
    animaRmvItemHeight->setEndValue(0);

    taskCheckTimer = new QTimer(this);
    taskCheckTimer->start(1000 * 60 * 1);

    this->setDragEnabled(true);        // 允许拖拽
    this->setAcceptDrops(true);        // 允许放置
    this->setSelectionMode(QAbstractItemView::SingleSelection); // 单选模式
    this->setDefaultDropAction(Qt::MoveAction); // 默认拖拽操作为移动

    // 关闭滚动条
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    LoadData();

    connect(animaRmvItemHeight, &QPropertyAnimation::valueChanged, this, [&](){
        deletedItem->setSizeHint(QSize(200, deletedItemHeight));
    });
    connect(animaRmvItemHeight, &QPropertyAnimation::finished, this, [&](){
        delete deletedItem;
    });
    connect(taskCheckTimer, &QTimer::timeout, this, &TaskView::CheckTaskTimeOut);
}

TaskView::~TaskView()
{
    SaveData();
}

void TaskView::AddTask(TaskInfo info)
{
    QListWidgetItem *item = new QListWidgetItem(this);
    info.SetContent(info.GetContent());
    TaskViewItem *vItem = new TaskViewItem(info, item, this);
    this->addItem(item);
    this->setItemWidget(item, vItem);

    connect(vItem, &TaskViewItem::Delete, this, &TaskView::RemoveItem);
    connect(vItem, &TaskViewItem::Complete, this, &TaskView::RemoveItem);
    connect(vItem, &TaskViewItem::Edit, this, [&](TaskViewItem* item){emit this->Edit(item);});
}

void TaskView::RemoveItem(QListWidgetItem *item)
{
    deletedItem = item;
    this->itemWidget(item)->disconnect();
    this->itemWidget(item)->deleteLater();
    this->removeItemWidget(item);
    animaRmvItemHeight->setStartValue(deletedItem->sizeHint().height());
    animaRmvItemHeight->start();
}

void TaskView::CheckTaskTimeOut()
{
    bool isChanged = false;
    for(int i = this->count() - 1; i >= 0; --i)
    {
        QListWidgetItem *item = this->item(i);
        TaskViewItem *vItem = dynamic_cast<TaskViewItem*>(this->itemWidget(item));
        TaskInfo itemInfo = vItem->GetTaskInfo();
        if(itemInfo.GetTime().date() < QDate::currentDate())
        {
            deletedItem = item;
            this->itemWidget(item)->disconnect();
            this->itemWidget(item)->deleteLater();
            this->removeItemWidget(item);
            delete item;
            isChanged = true;
        }
    }

    if(isChanged)
    {
        SaveData();
    }
}

void TaskView::LoadData()
{
    QJsonObject obj = FileManagement::Instance()->LoadJsonFile();

    int num = obj["num"].toInt();
    QJsonArray arr = obj["data"].toArray();
    for(int i = 0; i < arr.count(); ++i)
    {
        this->AddTask(TaskInfo::FromJson(arr[i].toObject()));
    }
}

void TaskView::SaveData()
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

