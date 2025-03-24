#include "TaskEditDialog.h"
#include "model/CountdownDayInfo.h"
#include "model/ScheduleInfo.h"
#include "model/TaskInfo.h"
#include "TimeEditor.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "utility/Utility.h"

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
        this->labelType->setText("任务");
        this->labelEndTime->hide();
        this->labelTime2->hide();
        timeEditor->hide();
    });
    connect(btnTypes[1], &QPushButton::clicked, this, [&](){
        this->labelType->setText("日程");
        this->labelEndTime->show();
        this->labelTime2->show();
        timeEditor->hide();
    });
    connect(btnTypes[2], &QPushButton::clicked, this, [&](){
        this->labelType->setText("倒数日");
        this->labelEndTime->hide();
        this->labelTime2->hide();
        timeEditor->hide();
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
        this->labelTime1->setText(Utility::FormatDateTime(time1));
        break;
    }
    case Model::task:{
        const TaskInfo *ti = static_cast<const TaskInfo*>(info);
        time1 = ti->GetTime();
        this->labelTime1->setText(Utility::FormatDateTime(time1));
        break;
    }
    case Model::schedule:{
        const ScheduleInfo *si = static_cast<const ScheduleInfo*>(info);
        time1 = si->GetSTime();
        this->labelTime1->setText(Utility::FormatDateTime(time1));
        time2 = si->GetETime();
        this->labelTime1->setText(Utility::FormatDateTime(time2));
        break;
    }
    default:
        break;
    }
}

BaseInfo* TaskEditDialog::GetTaskInfo()
{
    Model::ModelType key = Model::TypeToChinese.key(labelType->text());

    BaseInfo *info;
    switch (key) {
    case Model::countdown_day:
        return new CountdownDayInfo(lineEditor->text(), this->time1.date());
    case Model::schedule:
        return new ScheduleInfo(lineEditor->text(), time1, time2);;
    case Model::task:
        return new TaskInfo(lineEditor->text(), time1);
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
    timeEditor->resize(QSize(this->width(), itemHeight));
    timeEditor->move(this->geometry().left(), this->geometry().bottom() - itemHeight - 40);
    timeEditor->show();
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

bool TaskEditDialog::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(obj == labelTime1)
        {
            qDebug() << "label1";
            ShowTimeEditor();
            timeEditor->SetEditedLabel(labelTime1);
            timeEditor->SetEditedDateTime(&time1);
            return true;
        }
        else if(obj == labelTime2)
        {
            qDebug() << "label2";
            ShowTimeEditor();
            timeEditor->SetEditedLabel(labelTime2);
            timeEditor->SetEditedDateTime(&time2);
            return true;
        }
        else
        {
            qDebug() << "other";
            timeEditor->hide();
            timeEditor->SetEditedLabel(nullptr);
        }
    }

    return QObject::eventFilter(obj, event);
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
    labelTime1 = new QLabel(QDateTime::currentDateTime().toString(), this);
    labelTime2 = new QLabel(QDateTime::currentDateTime().toString(), this);

    labelTime1->installEventFilter(this);
    labelTime2->installEventFilter(this);

    timeEditor = new TimeEditor(this);
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
    lineEditor = new QLineEdit(this);
    lineEditor->setObjectName("taskedit_lineedit");
    vLayout->addWidget(lineEditor);

    QLabel *label2 = new QLabel("deadline", this);
    label2->setObjectName("taskedit_label");
    vLayout->addWidget(label2);

    labelTime1->setObjectName("tasledit_labeltime");
    labelTime2->setObjectName("tasledit_labeltime");
    vLayout->addWidget(labelTime1);

    labelEndTime = new QLabel("end time", this);
    labelEndTime->setObjectName("taskedit_label");
    vLayout->addWidget(labelEndTime);
    labelEndTime->hide();
    vLayout->addWidget(labelTime2);
    labelTime2->hide();

    vLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));


    // vLayout->addWidget(timeEditor);

    QHBoxLayout *hLayout2 = new QHBoxLayout();
    vLayout->addLayout(hLayout2, Qt::AlignBottom);

    hLayout2->addWidget(btnCancel);
    hLayout2->addWidget(btnConfirm);
}
