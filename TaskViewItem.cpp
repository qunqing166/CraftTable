#include "TaskViewItem.h"
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QRandomGenerator>

// TaskViewItem::TaskViewItem(QWidget *parent):QWidget(parent)
// {
//     ObjectInit();
//     WidgetInit();

//     connect(animaBtnWidth, &QPropertyAnimation::valueChanged, this, [&](){
//         btnComplete->setFixedWidth(btnWidth);
//         btnDelete->setFixedWidth(btnWidth);
//     });
//     connect(btnComplete, &QPushButton::clicked, this, [&](){emit Complete(item);});
//     connect(btnDelete, &QPushButton::clicked, this, [&](){emit Delete(item);});
// }

TaskViewItem::TaskViewItem(BaseInfo* info, QListWidgetItem *item, QWidget *parent)
{
    // this->info = info;
    this->info.reset(info);
    this->item = item;
    this->item->setSizeHint(QSize(200, 60));

    ObjectInit();
    WidgetInit();

    connect(animaBtnWidth, &QPropertyAnimation::valueChanged, this, [&](){
        btnComplete->setFixedWidth(btnWidth);
        btnDelete->setFixedWidth(btnWidth);
    });

    connect(btnComplete, &QPushButton::clicked, this, [&](){emit Complete(this->item);});
    connect(btnDelete, &QPushButton::clicked, this, [&](){emit Delete(this->item);});
}

void TaskViewItem::enterEvent(QEnterEvent *event)
{
    ShowBtn();
}

void TaskViewItem::leaveEvent(QEvent *event)
{
    HideBtn();
}

void TaskViewItem::mousePressEvent(QMouseEvent *event)
{
    HideBtn();
    emit Edit(this);
    event->accept();
}

void TaskViewItem::ObjectInit()
{
    animaBtnWidth = new QPropertyAnimation(this, "BtnWidth", this);
    animaBtnHeight = new QPropertyAnimation(this, "BtnHeight", this);
    animaBtnHeight->setStartValue(60);
    animaBtnHeight->setEndValue(0);

    btnComplete = new QPushButton("完成", this);
    btnDelete = new QPushButton("删除", this);

    labelContent = new QLabel(this);
    labelContent->setObjectName("task_content");
    labelDate = new QLabel(this);
    labelDate->setObjectName("task_date");
    UpdateInfo();
}

void TaskViewItem::WidgetInit()
{
    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    hLayout1->setContentsMargins(0, 0, 0, 0);
    this->setLayout(hLayout1);
    QWidget *widget = new QWidget(this);
    QVBoxLayout *vLayout1 = new QVBoxLayout(this);
    vLayout1->setContentsMargins(0, 0, 0, 0);
    hLayout1->addWidget(widget);
    hLayout1->addLayout(vLayout1);
    vLayout1->addWidget(btnComplete);
    vLayout1->addWidget(btnDelete);
    btnComplete->setFixedWidth(0);
    btnDelete->setFixedWidth(0);
    btnComplete->setObjectName("btn_item");
    btnDelete->setObjectName("btn_item");

    int id = QRandomGenerator::global()->bounded(4) + 1;
    widget->setObjectName("task_item" + QString::number(id));

    QLabel *label1 = new QLabel(this);
    label1->setFixedWidth(4);
    label1->setObjectName("task_label" + QString::number(id));

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    widget->setLayout(hLayout);
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setContentsMargins(0, 0, 0, 0);

    hLayout->addWidget(label1);
    hLayout->addLayout(vLayout);
    vLayout->addWidget(labelContent);
    vLayout->addWidget(labelDate);
}

void TaskViewItem::ShowBtn()
{
    animaBtnWidth->stop();
    animaBtnWidth->setStartValue(btnWidth);
    animaBtnWidth->setEndValue(40);
    animaBtnWidth->start();
}

void TaskViewItem::HideBtn()
{
    animaBtnWidth->stop();
    animaBtnWidth->setStartValue(btnWidth);
    animaBtnWidth->setEndValue(0);
    animaBtnWidth->start();
}

void TaskViewItem::UpdateInfo()
{
    this->labelContent->setText(this->info->Content());
    QString infoStr = QString("%1 | %2")
                          .arg(info->Type())
                          .arg(info->Time());
    this->labelDate->setText(infoStr);
}
void TaskViewItem::SetTaskInfo(BaseInfo* info) {
    this->info.reset(info);
    UpdateInfo();
}

void TaskViewItem::DisConnect()
{
    disconnect(animaBtnWidth, nullptr, this, nullptr);
    disconnect(btnComplete, nullptr, this, nullptr);
    disconnect(btnDelete, nullptr   , this, nullptr);
}
const BaseInfo *TaskViewItem::GetTaskInfo() const { return info.data(); }
