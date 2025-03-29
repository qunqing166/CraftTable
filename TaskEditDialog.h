#ifndef TASKEDITDIALOG_H
#define TASKEDITDIALOG_H

#include "TaskViewItem.h"
// #include "TimeEditor.h"
#include "UserControl/DateTimeEditor.h"
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



protected:
    virtual void closeEvent(QCloseEvent *event) override;
    void paintEvent(QPaintEvent *paintEvent) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:

    // void TaskCreated(TaskInfo);

private:

    void ObjectInit();
    void WidgetInit();

    void OnBtnConfirmClicked();
    void ShowTimeEditor();

    void ShowEditedItem(Model::ModelType);

    QLineEdit *lineEditor;
    QLabel *labelStartTime;
    QLabel *labelEndTime;
    // QLabel *labelTime;
    // TimeEditor *timeEditor;
    DateTimeEditor *timeEditor;

    TaskViewItem *editedItem = nullptr;
    OperationType op = create;
    // QScopedPointer<BaseInfo> info;

    QLabel *labelTime1;
    QLabel *labelTime2;

    QPushButton *btnCancel;
    QPushButton *btnConfirm;

    QLabel *labelType;
    QVector<QPushButton*>btnTypes;

    QDateTime time1;
    QDateTime time2;
};

#endif // TASKEDITDIALOG_H
