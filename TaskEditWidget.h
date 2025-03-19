#ifndef TASKEDITWIDGET_H
#define TASKEDITWIDGET_H

#include "TaskViewItem.h"
#include "TimeEditor.h"

#include <QLineEdit>
#include <QWidget>

enum OpType{
    edit,
    create
};

class TaskEditWidget : public QWidget
{
    Q_OBJECT

    QLineEdit *lineEditor;
    TimeEditor *timeEditor;
    OpType op;
    TaskViewItem *editedItem = nullptr;
    TaskInfo info;

public:
    explicit TaskEditWidget(QWidget *parent = nullptr);
    void SetOp(OpType type){this->op = type;}
    void SetEditedItem(TaskViewItem* item){this->editedItem = item;}
    void SetTaskInfo(TaskInfo info);

    void OnTaskEdit(TaskViewItem* item);
    void OnTaskCreate();

signals:
    void TaskCreated(TaskInfo);
};

#endif // TASKEDITWIDGET_H
