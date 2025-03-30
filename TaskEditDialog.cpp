#include "TaskEditDialog.h"
#include "model/CountdownDayInfo.h"
#include "model/ScheduleInfo.h"
#include "model/TaskInfo.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QPainter>
#include "utility/Utility.h"
#include "model/LongTaskInfo.h"

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
    this->installEventFilter(this);

    connect(btnCancel, &QPushButton::clicked, this, [&](){this->hide();});
    connect(btnConfirm, &QPushButton::clicked, this, &TaskEditDialog::OnBtnConfirmClicked);
    connect(btnTypes[0], &QPushButton::clicked, this, [&](){
        ShowEditedItem(Model::task);
    });
    connect(btnTypes[1], &QPushButton::clicked, this, [&](){
        ShowEditedItem(Model::long_task);
    });
    connect(btnTypes[2], &QPushButton::clicked, this, [&](){
        ShowEditedItem(Model::schedule);
    });
    connect(btnTypes[3], &QPushButton::clicked, this, [&](){
        ShowEditedItem(Model::countdown_day);
    });
    connect(timeEditor, &DateTimeEditor::ValueChanged, this, [&](const QDateTime& dt){
        if(labelEdited != nullptr && timeEdited != nullptr)
        {
            *timeEdited = dt;
            labelEdited->setText(Utility::FormatDateTime(dt));
            if(timeEdited == &time1 && time1 > time2)
            {
                time2 = time1;
                UpdateTimeLabel();
            }
        }
    });
}

TaskEditDialog::~TaskEditDialog()
{
}

void TaskEditDialog::SetTaskInfo(const BaseInfo *info)
{
    this->lineEditor->setText(info->Content());
    this->labelType->setText(info->Type());
    Model::ModelType type = Model::TypeToChinese.key(info->Type());
    switch (type) {
    case Model::countdown_day:{
        const CountdownDayInfo *ci = static_cast<const CountdownDayInfo*>(info);
        time1 = QDateTime(ci->GetTime(), QTime());
        /* 默认为起始时间的半小时后, 为了应对转为日程类型 */
        time2 = time1.addSecs(60 * 30);
        break;
    }
    case Model::task:{
        const TaskInfo *ti = static_cast<const TaskInfo*>(info);
        time1 = ti->GetTime();
        time2 = time1.addSecs(60 * 30);
        break;
    }
    case Model::schedule:{
        const ScheduleInfo *si = static_cast<const ScheduleInfo*>(info);
        time1 = si->GetSTime();
        time2 = si->GetETime();
        break;
    }
    default:
        break;
    }

    UpdateTimeLabel();
}

BaseInfo* TaskEditDialog::GetTaskInfo()
{
    Model::ModelType key = Model::TypeToChinese.key(labelType->text());

    switch (key) {
    case Model::countdown_day:
        return new CountdownDayInfo(lineEditor->text(), this->time1.date());
    case Model::schedule:
        return new ScheduleInfo(lineEditor->text(), time1, time2);;
    case Model::task:
        return new TaskInfo(lineEditor->text(), time1);
    case Model::long_task:
        return new LongTaskInfo(lineEditor->text(), time1.date());
    default:
        return nullptr;
    }
}

void TaskEditDialog::OnBtnConfirmClicked()
{
    this->setResult(QDialog::Accepted);
    this->hide();
}

void TaskEditDialog::ShowTimeEditor()
{
    const int itemHeight = 200;
    // timeEditor->SetCurrentDt()
    timeEditor->resize(QSize(this->width(), itemHeight));
    timeEditor->move(this->geometry().left(), this->geometry().bottom() - itemHeight - 40);
    timeEditor->show();
    // qDebug() << timeEditor->geometry();
}

void TaskEditDialog::UpdateTimeLabel()
{
    labelTime1->setText(Utility::FormatDateTime(time1));
    labelTime2->setText(Utility::FormatDateTime(time2));
}

void TaskEditDialog::ShowEditedItem(Model::ModelType type)
{
    this->labelType->setText(Model::TypeToChinese.value(type));
    timeEditor->hide();
    switch(type)
    {
    case Model::countdown_day:
        this->labelStartTime->setText("日期");
        this->labelEndTime->hide();
        this->labelTime2->hide();
        break;
    case Model::schedule:
        this->labelStartTime->setText("开始时间");
        this->labelEndTime->show();
        this->labelTime2->show();
        break;
    case Model::task:
        this->labelStartTime->setText("日期");
        this->labelEndTime->hide();
        this->labelTime2->hide();
        break;
    case Model::long_task:
        this->labelStartTime->setText("开始时间");
        this->labelEndTime->hide();
        this->labelTime2->hide();
    default:
        break;
    }

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

    QDialog::paintEvent(paintEvent);
}

bool TaskEditDialog::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(obj == labelTime1)
        {
            ShowTimeEditor();
            labelEdited = labelTime1;
            timeEdited = &time1;
            timeEditor->SetDateTime(time1);
            return true;
        }
        else if(obj == labelTime2)
        {
            ShowTimeEditor();
            labelEdited = labelTime2;
            timeEdited = &time2;
            timeEditor->SetDateTime(time2);
            return true;
        }
        else
        {
            timeEditor->hide();
            labelEdited = nullptr;
            timeEdited = nullptr;
        }
    }

    return QDialog::eventFilter(obj, event);
}

void TaskEditDialog::ObjectInit()
{
    lineEditor = new QLineEdit(this);
    lineEditor->setObjectName("taskedit_lineedit");

    btnCancel = new QPushButton("取消", this);
    btnCancel->setObjectName("editor_btn");
    btnConfirm = new QPushButton("确认", this);
    btnConfirm->setObjectName("editor_btn");
    labelType = new QLabel("任务", this);
    labelType->setAlignment(Qt::AlignCenter);
    labelType->setObjectName("taskedit_labeltype");

    // QStringList btnText{"任务", "日程", "倒数日"};
    QStringList btnText = Model::TypeToChinese.values();
    // btnTypes.resize(btnText.count());
    btnTypes.resize(btnText.count() - 1);
    for(int i = 0; i < btnText.count() - 1; ++i)
    {
        btnTypes[i] = new QPushButton(btnText[i + 1], this);
        btnTypes[i]->setObjectName("taskedit_btn");
        btnTypes[i]->setFixedWidth(45);
    }
    labelTime1 = new QLabel(Utility::FormatDateTime(QDateTime::currentDateTime()), this);
    labelTime2 = new QLabel(Utility::FormatDateTime(QDateTime::currentDateTime()), this);

    labelTime1->setObjectName("tasledit_labeltime");
    labelTime2->setObjectName("tasledit_labeltime");

    labelTime1->installEventFilter(this);
    labelTime2->installEventFilter(this);

    timeEditor = new DateTimeEditor(this);
    timeEditor->hide();

}

void TaskEditDialog::WidgetInit()
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
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

    vLayout->addWidget(lineEditor);

    labelStartTime = new QLabel(this);
    labelStartTime->setObjectName("taskedit_label");
    vLayout->addWidget(labelStartTime);
    vLayout->addWidget(labelTime1);

    labelEndTime = new QLabel("结束时间", this);
    labelEndTime->setObjectName("taskedit_label");
    vLayout->addWidget(labelEndTime);
    labelEndTime->hide();
    vLayout->addWidget(labelTime2);
    labelTime2->hide();

    vLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));


    QHBoxLayout *hLayout2 = new QHBoxLayout();
    vLayout->addLayout(hLayout2, Qt::AlignBottom);

    hLayout2->addWidget(btnCancel);
    hLayout2->addWidget(btnConfirm);

}
