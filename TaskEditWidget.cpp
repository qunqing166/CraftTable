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

    // QLabel *labelEmpty = new QLabel(this);
    // labelEmpty->setFixedHeight(200);
    // vLayout->addWidget(labelEmpty);

    QHBoxLayout *hLayout2 = new QHBoxLayout(this);
    vLayout->addLayout(hLayout2);

    QPushButton *btn1 = new QPushButton("取消", this);
    QPushButton *btn2 = new QPushButton("确认", this);
    hLayout2->addWidget(btn1);
    hLayout2->addWidget(btn2);

    connect(btn1, &QPushButton::clicked, this, [&](){
        this->hide();
    });
    connect(btn2, &QPushButton::clicked, this, [&](){
        TaskInfo info;
        info.SetInfo(lineEditor->text());
        qDebug() << info.GetInfo();
        if(op == OpType::edit)
        {
            editedItem->SetTaskInfo(info);
            editedItem = nullptr;
        }
        else if(op == OpType::create)
        {
            emit TaskCreated(info);
        }
        this->hide();
    });
}
void TaskEditWidget::SetTaskInfo(TaskInfo info)
{
    this->info = info;
    this->lineEditor->setText(info.GetInfo());
}

void TaskEditWidget::OnTaskEdit(TaskViewItem *item)
{
    this->SetTaskInfo(item->GetTaskInfo());
    this->SetEditedItem(item);
    this->SetOp(OpType::edit);
    this->show();
    qDebug() << "edit";
}

void TaskEditWidget::OnTaskCreate()
{
    this->SetTaskInfo(TaskInfo());
    this->SetOp(OpType::create);
    this->show();
    qDebug() << "creat";
}
