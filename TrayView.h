#ifndef TRAYVIEW_H
#define TRAYVIEW_H

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
    QLabel *label1;
    QLabel *label2;
    QStackedLayout *sLayout;
    TaskView *view;
    QPushButton *btnAdd;

public:
    TrayView(QWidget *parent = nullptr);
    ~TrayView();

    TaskView* GetTaskView(){return view;}

    void AddTask(TaskInfo info);

private:
    void ObjectInit();
    void WidgetInit();
    void CheckTrayIconMouseHover();

protected:
    void paintEvent(QPaintEvent*) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void CreateTask();

};

#endif // TRAYVIEW_H
