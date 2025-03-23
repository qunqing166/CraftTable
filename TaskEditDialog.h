#ifndef TASKEDITDIALOG_H
#define TASKEDITDIALOG_H

#include "TaskViewItem.h"
#include "TimeEditor.h"

#include <QLineEdit>
#include <QWidget>
#include <QDialog>

class TaskEditDialog : public QDialog
{
    Q_OBJECT

public:
    enum OperationType{
        edit,
        create
    };

    explicit TaskEditDialog(QWidget *parent = nullptr);
    ~TaskEditDialog();

    void SetOperationType(OperationType type){this->op = type;}
    void SetEditedItem(TaskViewItem* item){this->editedItem = item;}
    void SetTaskInfo(const BaseInfo* info);

    BaseInfo* GetTaskInfo();
    OperationType GetOperationType(){return op;};

public slots:

    // void OnTaskEdit(TaskViewItem* item);
    // void OnTaskCreate();

private slots:

    void OnBtnConfirmClicked();

protected:
    virtual void closeEvent(QCloseEvent *event) override;
    void paintEvent(QPaintEvent *paintEvent) override;

signals:
    // void TaskCreated(TaskInfo);

private:

    void ObjectInit();
    void WidgetInit();

    QLineEdit *lineEditor;
    // TimeEditor *timeEditor;

    TaskViewItem *editedItem = nullptr;
    OperationType op = create;
    // QScopedPointer<BaseInfo> info;
    QLabel *labelTime1;
    QLabel *labelTime2;

    QPushButton *btnCancel;
    QPushButton *btnConfirm;

    QLabel *labelType;
    QVector<QPushButton*>btnTypes;
    // TaskInfo::TaskType crtType = TaskInfo::task;

    // QStackedLayout *sLayout;
};

#endif // TASKEDITDIALOG_H
