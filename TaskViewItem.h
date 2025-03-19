#ifndef TASKVIEWITEM_H
#define TASKVIEWITEM_H

#include "TaskInfo.h"
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QListWidget>
#include <QLabel>

class TaskViewItem:public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int BtnWidth READ GetBtnWidth WRITE SetBtnWidth)
    Q_PROPERTY(int BtnHeight READ GetBtnHeight WRITE SetBtnHeight)

    int btnWidth = 0;
    int btnHeight = 0;

    QPushButton *btnComplete;
    QPushButton *btnDelete;
    QPropertyAnimation *animaBtnWidth;
    QPropertyAnimation *animaBtnHeight;
    QListWidgetItem *item;
    QLabel *labelData;

    TaskInfo info;

public:
    TaskViewItem(QWidget *parent = nullptr);
    TaskViewItem(const TaskInfo& info, QListWidgetItem* item, QWidget* parent = nullptr);

    int GetBtnWidth() const { return btnWidth; }
    void SetBtnWidth(int width) { btnWidth = width; }
    int GetBtnHeight() const {return btnHeight;}
    void SetBtnHeight(int height){this->btnHeight = height;}
    void SetTaskInfo(const TaskInfo& info){this->info = info, this->labelData->setText(this->info.GetContent());}
    TaskInfo GetTaskInfo(){return info;}
    void SetItem(QListWidgetItem *item){this->item = item;}

protected:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    // virtual void wheelEvent(QWheelEvent *event) override;

private:
    void ObjectInit();
    void WidgetInit();

    void ShowBtn();
    void HideBtn();

signals:
    void Complete(QListWidgetItem*);
    void Delete(QListWidgetItem*);
    void Edit(TaskViewItem*);

};

#endif // TASKVIEWITEM_H
