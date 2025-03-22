#ifndef TASKEDITWIDGET_H
#define TASKEDITWIDGET_H

#include "TaskViewItem.h"
#include "TimeEditor.h"

#include <QLineEdit>
#include <QWidget>

class TaskEditWidget : public QWidget
{
    Q_OBJECT

public:
    enum OperationType{
        edit,
        create
    };

    explicit TaskEditWidget(QWidget *parent = nullptr);
    ~TaskEditWidget();

    void SetOperationType(OperationType type){this->op = type;}
    void SetEditedItem(TaskViewItem* item){this->editedItem = item;}
    void SetTaskInfo(const TaskInfo& info);

public slots:

    void OnTaskEdit(TaskViewItem* item);
    void OnTaskCreate();

private slots:

    void OnBtnConfirmClicked();

signals:
    void TaskCreated(TaskInfo);

private:

    void ObjectInit();
    void WidgetInit();

    QLineEdit *lineEditor;
    TimeEditor *timeEditor;

    TaskViewItem *editedItem = nullptr;
    OperationType op;
    TaskInfo info;

    QPushButton *btnCancel;
    QPushButton *btnConfirm;

    QLabel *labelType;
    // QPushButton **btnTypes;
    QVector<QPushButton*>btnTypes;
    TaskInfo::TaskType crtType = TaskInfo::task;
};

#endif // TASKEDITWIDGET_H
