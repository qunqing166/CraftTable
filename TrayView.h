#ifndef TRAYVIEW_H
#define TRAYVIEW_H

#include "TaskEditDialog.h"
#include "TaskView.h"

#include <QSystemTrayIcon>
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QStackedLayout>

class TrayView: public QWidget
{
    Q_OBJECT

    QSystemTrayIcon *trayIcon;
    QTimer *hoverCheckTimer;
    QTimer *ishoverTimeoutTimer;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    TaskView *view;
    QPushButton *btnAdd;
    QLabel *labelDate;
    QLabel *labelWeekday;
    // TaskViewItem *editedItem = nullptr;

    // TaskEditWidget* editor = nullptr;

public:
    TrayView(QWidget *parent = nullptr);
    ~TrayView();

    TaskView* GetTaskView(){return view;}

    // void AddTask(const BaseInfo info);
    void UpdateDate();

private:
    void ObjectInit();
    void WidgetInit();
    void CheckTrayIconMouseHover();

    // void EditTaskInfo(TaskEditDialog::OperationType type);

    void OnBtnAddClicked();

protected:
    void paintEvent(QPaintEvent*) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void CreateTask();

};

#endif // TRAYVIEW_H
