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
        btn1->setFixedWidth(btnWidth);
        btn2->setFixedWidth(btnWidth);
    });
    connect(btn1, &QPushButton::clicked, this, [&](){emit Complete(item);});
    connect(btn2, &QPushButton::clicked, this, [&](){emit Delete(item);});
}

TaskViewItem::TaskViewItem(const TaskInfo &info, QListWidgetItem *item, QWidget *parent)
{
    this->info = info;
    this->item = item;
    this->item->setSizeHint(QSize(200, 60));

    ObjectInit();
    WidgetInit();

    // this->setAttribute(Qt::WA_StyledBackground);

    connect(animaBtnWidth, &QPropertyAnimation::valueChanged, this, [&](){
        btn1->setFixedWidth(btnWidth);
        btn2->setFixedWidth(btnWidth);
    });

    connect(btn1, &QPushButton::clicked, this, [&](){emit Complete(this->item);});
    connect(btn2, &QPushButton::clicked, this, [&](){emit Delete(this->item);});
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

    btn1 = new QPushButton("完成", this);
    btn2 = new QPushButton("删除", this);
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
    vLayout1->addWidget(btn1);
    vLayout1->addWidget(btn2);
    btn1->setFixedWidth(0);
    btn2->setFixedWidth(0);
    btn1->setStyleSheet(R"(
            background-color:#cfcfcf;
            color:black;
    )");
    btn2->setStyleSheet(R"(
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

    labelData = new QLabel(this->info.GetInfo(), this);
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
