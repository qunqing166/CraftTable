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
    for(int i = this->infoList.count() - 1; i >= 0; --i)
    {
        delete *infoList[i];
        delete infoList[i];
    }
}

void TaskView::AddTask(BaseInfo** info)
{
    QListWidgetItem *item = new QListWidgetItem(this);
    TaskViewItem *vItem = new TaskViewItem(info, item, this);
    this->addItem(item);
    this->setItemWidget(item, vItem);

    connect(vItem, &TaskViewItem::Delete, this, &TaskView::OnItemRemove);
    connect(vItem, &TaskViewItem::Complete, this, &TaskView::OnItemComplete);
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
            BaseInfo** p(new BaseInfo*);
            *p = editor.GetTaskInfo();
            infoList.append(p);
            this->AddTask(p);
            // this->AddTask(editor.GetTaskInfo());
        }
        else if(editor.GetOperationType() == TaskEditDialog::edit)
        {
            editedItem->SetTaskInfo(editor.GetTaskInfo());
        }
    }

    SaveData();
}

void TaskView::OnItemRemove(QListWidgetItem *item)
{
    deletedItem = item;

    TaskViewItem *vItem = dynamic_cast<TaskViewItem*>(itemWidget(item));

    for(int i = 0; i < infoList.count(); ++i)
    {
        if(*infoList[i] == vItem->GetTaskInfo())
        {
            delete *infoList[i];
            delete infoList[i];
            infoList.remove(i);
            break;
        }
    }

    qDebug() << "list count: " << infoList.count();

    vItem->deleteLater();
    this->removeItemWidget(item);
    animaRmvItemHeight->setStartValue(deletedItem->sizeHint().height());
    animaRmvItemHeight->start();
}

void TaskView::RemoveItemBack(QListWidgetItem *item)
{
    this->itemWidget(item)->deleteLater();
    this->removeItemWidget(item);
    delete item;
}

void TaskView::Clear()
{
    for(int i = this->count() - 1; i >= 0; --i)
    {
        this->RemoveItemBack(this->item(i));
    }
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

        BaseInfo** p(new BaseInfo*);
        infoList.append(p);
        *p = info;

    }

    this->ShowByDate(QDate::currentDate());
}

void TaskView::SaveData()
{
    QJsonObject obj;
    obj.insert("num", this->count());

    QJsonArray array;
    for(int i = 0; i < infoList.count(); ++i)
    {
        array.append((*infoList[i])->ToJson());
    }

    obj.insert("data", array);

    FileManagement::Instance()->SaveJsonFile(obj);

    qDebug() << obj;
}

void TaskView::ShowAll()
{
    this->Clear();
    for(int i = 0; i < infoList.count(); ++i)
    {
        this->AddTask(infoList[i]);
    }
}

void TaskView::ShowByDate(const QDate &date)
{
    this->Clear();

    int dDays = QDate::currentDate().daysTo(date);

    for(int i = 0; i < infoList.count(); ++i)
    {
        BaseInfo* bi = *infoList[i];


        Model::ModelType t = Model::TypeToChinese.key(bi->Type());

        switch(t)
        {
        case Model::task:{
            TaskInfo* ti = dynamic_cast<TaskInfo*>(bi);
            if(ti->GetTime().date() == QDate::currentDate().addDays(dDays))
            {
                this->AddTask(infoList[i]);
            }
            break;
        }
        case Model::schedule:{
            ScheduleInfo* si = dynamic_cast<ScheduleInfo*>(bi);
            if(si->GetTime().date() == QDate::currentDate().addDays(dDays))
            {
                this->AddTask(infoList[i]);
            }
            break;
        }
        case Model::countdown_day:{
            CountdownDayInfo* ci = dynamic_cast<CountdownDayInfo*>(bi);
            if(ci->GetTime() == QDate::currentDate().addDays(dDays))
            {
                this->AddTask(infoList[i]);
            }
            break;
        }
        default:
            break;
        }
    }
}

void TaskView::OnItemComplete(QListWidgetItem *item)
{
    deletedItem = item;
    this->itemWidget(item)->disconnect();
    this->itemWidget(item)->deleteLater();
    this->removeItemWidget(item);
    animaRmvItemHeight->setStartValue(deletedItem->sizeHint().height());
    animaRmvItemHeight->start();
}

