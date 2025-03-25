#ifndef TASKVIEWITEM_H
#define TASKVIEWITEM_H

#include "model/BaseInfo.h"
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QListWidget>
#include <QLabel>
#include <QEnterEvent>

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
    QLabel *labelContent;
    QLabel *labelDate;

    // QSharedPointer<BaseInfo*> info;
    BaseInfo** info;


public:
    // TaskViewItem(QWidget *parent = nullptr);
    TaskViewItem(BaseInfo** info, QListWidgetItem* item, QWidget* parent = nullptr);
    ~TaskViewItem();

    int GetBtnWidth() const { return btnWidth; }
    void SetBtnWidth(int width) { btnWidth = width; }
    int GetBtnHeight() const {return btnHeight;}
    void SetBtnHeight(int height){this->btnHeight = height;}

    void SetTaskInfo(BaseInfo* info);
    BaseInfo *GetTaskInfo() const { return *info; }

    void SetItem(QListWidgetItem *item){this->item = item;}

    void DisConnect();

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

    void UpdateInfo();

signals:
    void Complete(QListWidgetItem*);
    void Delete(QListWidgetItem*);
    void Edit(TaskViewItem*);

};

#endif // TASKVIEWITEM_H
