#ifndef TASKVIEW_H
#define TASKVIEW_H

#include "TaskEditDialog.h"
#include "TaskViewItem.h"

#include <QObject>
#include <QListWidget>
#include <QPropertyAnimation>
#include <QTimer>

class TaskView: public QListWidget
{
    Q_OBJECT

    Q_PROPERTY(int DeletedItemHeight READ GetDeletedItemHeight WRITE SetDeletedItemHeight)

    int deletedItemHeight;

    QListWidgetItem *deletedItem = nullptr;
    QPropertyAnimation *animaRmvItemHeight;

    QTimer *taskCheckTimer;

    TaskViewItem* editedItem = nullptr;

public:
    TaskView(QWidget *parent = nullptr);
    ~TaskView();

    void AddTask(TaskInfo info);

    void EditTaskInfo(TaskEditDialog::OperationType);

private:
    int GetDeletedItemHeight(){return deletedItemHeight;}
    void SetDeletedItemHeight(int height){this->deletedItemHeight = height;}
    void RemoveItem(QListWidgetItem *item);
    void CheckTaskTimeOut();

    void LoadData();
    void SaveData();

signals:
    void Edit(TaskViewItem*);
    void Add();

};

#endif // TASKVIEW_H
