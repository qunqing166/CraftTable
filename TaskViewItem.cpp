#include "TaskViewItem.h"
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QRandomGenerator>

TaskViewItem::TaskViewItem(BaseInfo** info, QListWidgetItem *item, QWidget *parent):
    info(info), item(item)
{
    this->item->setSizeHint(QSize(200, 60));

    ObjectInit();
    WidgetInit();

    connect(animaBtnWidth, &QPropertyAnimation::valueChanged, this, [&](){
        btnComplete->setFixedWidth(btnWidth);
        btnDelete->setFixedWidth(btnWidth);
    });
    connect(animaClicked, &QPropertyAnimation::valueChanged, this, [&](){
        this->setContentsMargins(margin, margin, margin, margin);
    });
    connect(animaClicked, &QPropertyAnimation::finished, this, [&](){
        if(margin == 0)
        {
            emit Edit(this);
        }
    });

    connect(btnComplete, &QPushButton::clicked, this, [&](){emit Complete(this->item);});
    connect(btnDelete, &QPushButton::clicked, this, [&](){emit Delete(this->item);});

}

TaskViewItem::~TaskViewItem()
{
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

    animaClicked->setStartValue(margin);
    animaClicked->setEndValue(5);
    this->animaClicked->start();
    event->accept();
}

void TaskViewItem::mouseReleaseEvent(QMouseEvent *event)
{
    animaClicked->stop();
    animaClicked->setStartValue(margin);
    animaClicked->setEndValue(0);
    animaClicked->start();

    // emit Edit(this);

    event->accept();
}

void TaskViewItem::ObjectInit()
{


    animaBtnWidth = new QPropertyAnimation(this, "BtnWidth", this);
    animaBtnWidth->setDuration(150);

    animaBtnHeight = new QPropertyAnimation(this, "BtnHeight", this);
    animaBtnHeight->setStartValue(60);
    animaBtnHeight->setEndValue(0);

    animaClicked = new QPropertyAnimation(this, "Margin", this);
    this->animaClicked->setDuration(100);

    btnComplete = new QPushButton("完成", this);
    btnDelete = new QPushButton("删除", this);
    btnComplete->setObjectName("btn_item");
    btnDelete->setObjectName("btn_item");

    labelContent = new QLabel(this);
    labelContent->setObjectName("task_content");
    labelDate = new QLabel(this);
    labelDate->setObjectName("task_date");
    UpdateInfo();
}

void TaskViewItem::WidgetInit()
{
    QHBoxLayout *hLayout1 = new QHBoxLayout();
    hLayout1->setContentsMargins(0, 0, 0, 0);
    this->setLayout(hLayout1);
    QWidget *widget = new QWidget(this);
    QVBoxLayout *vLayout1 = new QVBoxLayout();
    vLayout1->setContentsMargins(0, 0, 0, 0);
    hLayout1->addWidget(widget);
    hLayout1->addLayout(vLayout1);
    vLayout1->addWidget(btnComplete);
    vLayout1->addWidget(btnDelete);
    btnComplete->setFixedWidth(0);
    btnDelete->setFixedWidth(0);

    // 获取颜色
    int id = Model::TypeToChinese.key((*info)->Type());

    widget->setObjectName("task_item");
    widget->setStyleSheet(QString(R"(
        QWidget#task_item{
            background-color:%1;
            margin: 2px;
            border-radius: 15px;
        }
    )").arg(Model::TypeToColor.value((Model::ModelType)id).second.name()));

    QLabel *label1 = new QLabel(this);
    label1->setFixedWidth(4);
    label1->setObjectName("task_label");
    label1->setStyleSheet(QString(R"(
        QLabel#task_label{
            background-color:%1;
            border-radius:2px;
        }
    )").arg(Model::TypeToColor.value((Model::ModelType)id).first.name()));

    QHBoxLayout *hLayout = new QHBoxLayout();
    widget->setLayout(hLayout);
    QVBoxLayout *vLayout = new QVBoxLayout();
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
    this->labelContent->setText((*info)->Content());
    QString infoStr = QString("%1 | %2")
                          .arg((*info)->Type())
                          .arg((*info)->Time());
    this->labelDate->setText(infoStr);
}
void TaskViewItem::SetTaskInfo(BaseInfo* info) {
    delete *this->info;
    *this->info = info;
    UpdateInfo();
}

void TaskViewItem::DisConnect()
{
    disconnect(animaBtnWidth, nullptr, this, nullptr);
    disconnect(btnComplete, nullptr, this, nullptr);
    disconnect(btnDelete, nullptr   , this, nullptr);
}

