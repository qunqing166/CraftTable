#ifndef TASKVIEW_H
#define TASKVIEW_H

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

public:
    TaskView(QWidget *parent = nullptr);
    ~TaskView();

    void AddTask(TaskInfo info);

private:
    int GetDeletedItemHeight(){return deletedItemHeight;}
    void SetDeletedItemHeight(int height){this->deletedItemHeight = height;}
    void OnItemRemoved(QListWidgetItem *item);

    void LoadData();
    void SaveData();

signals:
    void Edit(TaskViewItem*);
    void Add();

};

#endif // TASKVIEW_H
