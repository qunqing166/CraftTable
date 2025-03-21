#include "TaskEditWidget.h"
#include "TaskInfo.h"
#include "TimeEditor.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

TaskEditWidget::TaskEditWidget(QWidget *parent)
    : QWidget{parent}
{
    ObjectInit();
    WidgetInit();

    connect(btnCancel, &QPushButton::clicked, this, [&](){this->hide();});
    connect(btnConfirm, &QPushButton::clicked, this, &TaskEditWidget::OnBtnConfirmClicked);
    connect(btnTypes[0], &QPushButton::clicked, this, [&](){
        this->labelType->setText("任务");crtType = TaskInfo::task;
    });
    connect(btnTypes[1], &QPushButton::clicked, this, [&](){
        this->labelType->setText("倒数日");crtType = TaskInfo::countdown_day;
    });
}

void TaskEditWidget::SetTaskInfo(const TaskInfo& info)
{
    this->info = info;
    this->lineEditor->setText(this->info.GetContent());
}

void TaskEditWidget::OnTaskEdit(TaskViewItem *item)
{
    this->SetTaskInfo(item->GetTaskInfo());
    this->SetEditedItem(item);
    this->SetOperationType(OperationType::edit);
    this->show();
}

void TaskEditWidget::OnTaskCreate()
{
    this->SetTaskInfo(TaskInfo());
    this->SetOperationType(OperationType::create);
    this->show();
}

void TaskEditWidget::OnBtnConfirmClicked()
{
    TaskInfo info{lineEditor->text(), this->crtType, timeEditor->GetDateTime()};
    // info.SetContent(lineEditor->text());
    // info.Set
    // qDebug() << info.GetContent();

    if(op == OperationType::edit)
    {
        editedItem->SetTaskInfo(info);
        editedItem = nullptr;
    }
    else if(op == OperationType::create)
    {
        emit TaskCreated(info);
    }
    this->hide();
}

void TaskEditWidget::ObjectInit()
{
    btnCancel = new QPushButton("取消", this);
    btnConfirm = new QPushButton("确认", this);
    labelType = new QLabel("任务", this);
    labelType->setAlignment(Qt::AlignCenter);

    QStringList btnText{"任务", "倒数日"};
    btnTypes.resize(btnText.count());
    for(int i = 0; i < btnText.count(); ++i)
    {
        btnTypes[i] = new QPushButton(btnText[i], this);
    }
}

void TaskEditWidget::WidgetInit()
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    this->setLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);


    QHBoxLayout *hLayout = new QHBoxLayout(this);
    vLayout->addLayout(hLayout);

    for(int i = 0; i < btnTypes.count(); ++i)
    {
        hLayout->addWidget(btnTypes[i]);
    }

    QFrame *frame = new QFrame(this);
    frame->setFixedHeight(2);
    frame->setStyleSheet(R"(
        background-color:white;
    )");
    vLayout->addWidget(frame);

    vLayout->addWidget(labelType);

    vLayout->addWidget(new QLabel("content", this));
    lineEditor = new QLineEdit(this);
    vLayout->addWidget(lineEditor);

    vLayout->addWidget(new QLabel("deadline"));

    timeEditor = new TimeEditor(this);
    vLayout->addWidget(timeEditor);

    QHBoxLayout *hLayout2 = new QHBoxLayout(this);
    vLayout->addLayout(hLayout2);

    hLayout2->addWidget(btnCancel);
    hLayout2->addWidget(btnConfirm);
}
