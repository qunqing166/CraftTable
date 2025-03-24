#include "TaskEditDialog.h"
#include "model/CountdownDayInfo.h"
#include "model/ScheduleInfo.h"
#include "model/TaskInfo.h"
#include "TimeEditor.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

TaskEditDialog::TaskEditDialog(QWidget *parent)
    : QDialog{parent}
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_StyledBackground);
    // this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::FramelessWindowHint);

    ObjectInit();
    WidgetInit();

    this->setObjectName("TaskEditDialog");

    connect(btnCancel, &QPushButton::clicked, this, [&](){this->hide();});
    connect(btnConfirm, &QPushButton::clicked, this, &TaskEditDialog::OnBtnConfirmClicked);
    connect(btnTypes[0], &QPushButton::clicked, this, [&](){
        this->labelType->setText("任务");//crtType = TaskInfo::task;
    });
    connect(btnTypes[1], &QPushButton::clicked, this, [&](){
        this->labelType->setText("日程");//crtType = TaskInfo::schedule;
    });
    connect(btnTypes[2], &QPushButton::clicked, this, [&](){
        this->labelType->setText("倒数日");//crtType = TaskInfo::countdown_day;
    });

}

TaskEditDialog::~TaskEditDialog()
{
    qDebug() << "TaskEditWidget delete";
}

void TaskEditDialog::SetTaskInfo(const BaseInfo *info)
{
    this->lineEditor->setText(info->Content());
    this->labelType->setText(info->Type());
}

BaseInfo* TaskEditDialog::GetTaskInfo()
{
    Model::ModelType key = Model::TypeToChinese.key(labelType->text());

    BaseInfo *info;
    switch (key) {
    case Model::countdown_day:
        return new CountdownDayInfo(lineEditor->text(), QDate::currentDate());
    case Model::schedule:
        return new ScheduleInfo(lineEditor->text(), QDateTime::currentDateTime(), QDateTime::currentDateTime());;
    case Model::task:
        return new TaskInfo(lineEditor->text(), QDateTime::currentDateTime());;
    default:
        return nullptr;
    }
}

void TaskEditDialog::OnBtnConfirmClicked()
{
    this->setResult(QDialog::Accepted);
    this->hide();
}

void TaskEditDialog::closeEvent(QCloseEvent *event)
{
    this->hide();
    event->ignore();
}

void TaskEditDialog::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(palette().color(QPalette::Window));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), 15, 15);

    QWidget::paintEvent(paintEvent);
}

void TaskEditDialog::ObjectInit()
{
    btnCancel = new QPushButton("取消", this);
    btnConfirm = new QPushButton("确认", this);
    labelType = new QLabel("任务", this);
    labelType->setAlignment(Qt::AlignCenter);
    labelType->setObjectName("taskedit_labeltype");

    QStringList btnText{"任务", "日程", "倒数日"};
    btnTypes.resize(btnText.count());
    for(int i = 0; i < btnText.count(); ++i)
    {
        btnTypes[i] = new QPushButton(btnText[i], this);
        btnTypes[i]->setObjectName("taskedit_btn");
    }
    labelTime1 = new QLabel(this);
    labelTime2 = new QLabel(this);
}

void TaskEditDialog::WidgetInit()
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    // this->setLayout(vLayout);
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

    QLabel *label1 = new QLabel("content", this);
    label1->setObjectName("taskedit_label");
    vLayout->addWidget(label1);
    lineEditor = new QLineEdit(this);
    vLayout->addWidget(lineEditor);

    QLabel *label2 = new QLabel("deadline", this);
    label2->setObjectName("taskedit_label");
    vLayout->addWidget(label2);

    // timeEditor = new TimeEditor(this);
    // vLayout->addWidget(timeEditor);

    QHBoxLayout *hLayout2 = new QHBoxLayout(this);
    vLayout->addLayout(hLayout2);

    hLayout2->addWidget(btnCancel);
    hLayout2->addWidget(btnConfirm);
}
