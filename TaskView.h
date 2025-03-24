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

    QList<BaseInfo**> infoList;

public:

    enum ShowType{
        today,
        tomorrow,
        all
    };

    TaskView(QWidget *parent = nullptr);
    ~TaskView();

    void AddTask(BaseInfo** info);

    void EditTaskInfo(TaskEditDialog::OperationType);

    void ShowAll();
    void ShowByDate(const QDate& date);

private:
    int GetDeletedItemHeight(){return deletedItemHeight;}
    void SetDeletedItemHeight(int height){this->deletedItemHeight = height;}
    void OnItemComplete(QListWidgetItem *item);
    void OnItemRemove(QListWidgetItem *item);
    void RemoveItemBack(QListWidgetItem *item);
    void Clear();
    void CheckTaskTimeOut();

    void LoadData();
    void SaveData();


signals:
    void Edit(TaskViewItem*);
    void Add();

};

#endif // TASKVIEW_H
