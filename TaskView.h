#ifndef TASKVIEW_H
#define TASKVIEW_H

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

private:
    int GetRmvItemHeight(){return rmvItemHeight;}
    void SetRmvItemHeight(int height){this->rmvItemHeight = height;}

    void OnItemRemove(QListWidgetItem *item);

};

#endif // TASKVIEW_H
