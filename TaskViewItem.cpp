#include "TaskViewItem.h"
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>

TaskViewItem::TaskViewItem(QWidget *parent):QWidget(parent)
{
    ObjectInit();
    WidgetInit();

    connect(animaBtnWidth, &QPropertyAnimation::valueChanged, this, [&](){
        btnComplete->setFixedWidth(btnWidth);
        btnDelete->setFixedWidth(btnWidth);
    });
    connect(btnComplete, &QPushButton::clicked, this, [&](){emit Complete(item);});
    connect(btnDelete, &QPushButton::clicked, this, [&](){emit Delete(item);});
}

TaskViewItem::TaskViewItem(const TaskInfo &info, QListWidgetItem *item, QWidget *parent)
{
    this->info = info;
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
    labelData = new QLabel("label", this);
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
    btnComplete->setStyleSheet(R"(
            background-color:#cfcfcf;
            color:black;
    )");
    btnDelete->setStyleSheet(R"(
            background-color:#cfcfcf;
            color:black;
    )");

    widget->setStyleSheet(R"(
            background-color:#fc9e98;
            margin: 2px;
            border-radius: 15px;
    )");
    QLabel *label1 = new QLabel(this);
    label1->setFixedWidth(6);
    label1->setStyleSheet(R"(
            background-color: yellow;
            border-radius:3px;
    )");

    labelData = new QLabel(this->info.GetContent(), this);
    QLabel *labelDate = new QLabel("2025/2/18  21:00", this);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    widget->setLayout(hLayout);
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setContentsMargins(0, 0, 0, 0);

    hLayout->addWidget(label1);
    hLayout->addLayout(vLayout);
    vLayout->addWidget(labelData);
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
