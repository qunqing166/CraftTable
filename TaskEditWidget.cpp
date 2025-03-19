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
    TaskInfo info;
    info.SetContent(lineEditor->text());
    qDebug() << info.GetContent();
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
}

void TaskEditWidget::WidgetInit()
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    this->setLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    vLayout->addLayout(hLayout);

    QPushButton *btnType1 = new QPushButton(this);
    QPushButton *btnType2 = new QPushButton(this);
    QPushButton *btnType3 = new QPushButton(this);
    QPushButton *btnType4 = new QPushButton(this);
    hLayout->addWidget(btnType1);
    hLayout->addWidget(btnType2);
    hLayout->addWidget(btnType3);
    hLayout->addWidget(btnType4);

    vLayout->addWidget(new QLabel("task", this));
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
