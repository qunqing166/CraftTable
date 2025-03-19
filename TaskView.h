#ifndef TASKVIEW_H
#define TASKVIEW_H

#include "TaskViewItem.h"

#include <QObject>
#include <QListWidget>
#include <QPropertyAnimation>

class TaskView: public QListWidget
{
    Q_OBJECT

    Q_PROPERTY(int RmvItemHeight READ GetRmvItemHeight WRITE SetRmvItemHeight)

    int rmvItemHeight;

    QListWidgetItem *removedItem = nullptr;
    QPropertyAnimation *animaRmvItemHeight;

public:
    TaskView(QWidget *parent = nullptr);
    ~TaskView();

    void AddTask(TaskInfo info);

private:
    int GetRmvItemHeight(){return rmvItemHeight;}
    void SetRmvItemHeight(int height){this->rmvItemHeight = height;}

    void OnItemRemove(QListWidgetItem *item);

    void Load();
    void Save();

signals:
    void Edit(TaskViewItem*);
    void Add();

};

#endif // TASKVIEW_H
