#include "FileManagement.h"
#include "TaskView.h"
#include "TaskViewItem.h"
#include "model/CountdownDayInfo.h"
#include "model/ScheduleInfo.h"
#include "model/TaskInfo.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "model/ModelType.h"

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

void TaskView::AddTask(BaseInfo* info)
{
    QListWidgetItem *item = new QListWidgetItem(this);
    // info.SetContent(info.GetContent());
    TaskViewItem *vItem = new TaskViewItem(info, item, this);
    this->addItem(item);
    this->setItemWidget(item, vItem);

    connect(vItem, &TaskViewItem::Delete, this, &TaskView::RemoveItem);
    connect(vItem, &TaskViewItem::Complete, this, &TaskView::RemoveItem);
    connect(vItem, &TaskViewItem::Edit, this, [&](TaskViewItem* item){
        this->editedItem = item;
        EditTaskInfo(TaskEditDialog::edit);
    });
}

void TaskView::EditTaskInfo(TaskEditDialog::OperationType type)
{
    /* 打开编辑窗口 */
    TaskEditDialog editor;
    editor.resize(250, 500);
    editor.SetOperationType(type);


    if(type == TaskEditDialog::edit)
    {
        editor.SetTaskInfo(editedItem->GetTaskInfo());
    }
    if(editor.exec() == QDialog::Accepted)
    {
        if(editor.GetOperationType() == TaskEditDialog::create)
        {
            this->AddTask(editor.GetTaskInfo());
        }
        else if(editor.GetOperationType() == TaskEditDialog::edit)
        {
            editedItem->SetTaskInfo(editor.GetTaskInfo());
        }
    }
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
        const BaseInfo* itemInfo = vItem->GetTaskInfo();
        if(itemInfo->IsTimeout())
        {
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
    qDebug() << "load";
    QJsonObject obj = FileManagement::Instance()->LoadJsonFile();

    int num = obj["num"].toInt();
    QJsonArray arr = obj["data"].toArray();

    for(int i = 0; i < arr.count(); ++i)
    {
        QJsonObject&& obj1 = arr[i].toObject();
        BaseInfo *info;
        Model::ModelType mType = Model::TypeToStr.key(obj1["type"].toString());

        switch(mType)
        {
        case Model::countdown_day:
            info = new CountdownDayInfo(arr[i].toObject());
            break;
        case Model::task:
            info = new TaskInfo(arr[i].toObject());
            break;
        case Model::schedule:
            info = new ScheduleInfo(arr[i].toObject());
            break;
        default:
            /* 不存在类型直接跳过 */
            info = nullptr;
            continue;
            break;
        }

        this->AddTask(info);
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
        array.append(itemWidget->GetTaskInfo()->ToJson());
    }

    obj.insert("data", array);

    FileManagement::Instance()->SaveJsonFile(obj);

    qDebug() << obj;
}

