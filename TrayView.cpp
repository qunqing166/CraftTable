#include "TaskView.h"
#include "TimeEditor.h"
#include "TrayView.h"
#include <QMenu>
#include <QAction>
#include <QCursor>
#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QEvent>
#include <QStandardPaths>
#include <QDir>
#include <QApplication>
#include <QPaintEvent>

TrayView::TrayView(QWidget *parent):QWidget(parent)
{
    this->setFixedSize(250, 500);
    ObjectInit();
    WidgetInit();
    UpdateDate();

    connect(btnAdd, &QPushButton::clicked, this, &TrayView::OnBtnAddClicked);
}

TrayView::~TrayView()
{
}

void TrayView::UpdateDate()
{
    QDateTime&& dt = QDateTime::currentDateTime();
    QString dtStr = QString("%1/%2").arg(dt.date().month()).arg(dt.date().day());
    labelDate->setText(dtStr);
    labelWeekday->setText(TimeEditor::GetDayOfWeek(dt.date().dayOfWeek()));
}

void TrayView::ObjectInit()
{
    trayIcon = new QSystemTrayIcon(this);
    hoverCheckTimer = new QTimer(this);
    ishoverTimeoutTimer = new QTimer(this);
    trayIcon->setIcon(QIcon("C:\\Users\\qunqing\\Desktop\\图片\\新建文件夹 (2)\\hj.png"));

    QMenu *trayMenu = new QMenu(this);
    QAction *restoreAction = new QAction("Restore", this);
    QAction *quitAction = new QAction("Quit", this);

    trayMenu->addAction(restoreAction);
    trayMenu->addAction(quitAction);

    connect(restoreAction, &QAction::triggered, this, &TrayView::showNormal);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    btnAdd = new QPushButton("+", this);
    btnAdd->setObjectName("btn_add");
    btnAdd->setFixedSize(30, 30);

    labelDate = new QLabel(this);
    labelDate->setObjectName("label_date");
    labelWeekday = new QLabel(this);
    labelWeekday->setObjectName("label_weekday");

    hoverCheckTimer->start(20);
    connect(hoverCheckTimer, &QTimer::timeout, this, &TrayView::CheckTrayIconMouseHover);
    connect(ishoverTimeoutTimer, &QTimer::timeout, ishoverTimeoutTimer, &QTimer::stop);
}

void TrayView::WidgetInit()
{
    // this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setAlignment(Qt::AlignTop);
    vLayout->setContentsMargins(4, 10, 4, 4);
    // this->setLayout(vLayout);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setAlignment(Qt::AlignLeft);
    vLayout->addLayout(hLayout);
    hLayout->setContentsMargins(10, 5, 5, 2);

    hLayout->addWidget(labelDate);
    hLayout->addWidget(labelWeekday);
    QLabel *labelEmpty = new QLabel(this);
    labelEmpty->setFixedWidth(100);
    hLayout->addWidget(labelEmpty);
    hLayout->addWidget(btnAdd);
    sLayout = new QStackedLayout();
    vLayout->addLayout(sLayout);

    view = new TaskView(this);
    sLayout->addWidget(view);
    QWidget *widget = new QWidget(this);
    sLayout->addWidget(widget);
    sLayout->setCurrentIndex(0);

    QHBoxLayout *hLayout1 = new QHBoxLayout();
    vLayout->addLayout(hLayout1);

    label1 = new QLabel("all", this);
    label1->setObjectName("TrayView_bottonlabel");
    label1->setAlignment(Qt::AlignHCenter);
    label2 = new QLabel("tomorrow", this);
    label2->setObjectName("TrayView_bottonlabel");
    label2->setAlignment(Qt::AlignHCenter);
    label3 = new QLabel("today", this);
    label3->setObjectName("TrayView_bottonlabel");
    label3->setAlignment(Qt::AlignHCenter);
    hLayout1->addWidget(label1);
    hLayout1->addWidget(label2);
    hLayout1->addWidget(label3);

    label1->installEventFilter(this);
    label2->installEventFilter(this);
    label3->installEventFilter(this);
}

void TrayView::CheckTrayIconMouseHover()
{
    if(trayIcon->geometry().contains(QCursor::pos()))
    {
        this->move(trayIcon->geometry().topLeft() - QPoint(this->width() / 4 * 3, this->height()));
        this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
        this->show();
        ishoverTimeoutTimer->start(200);
    }
    else
    {
        if(ishoverTimeoutTimer->isActive())
        {
            if(this->geometry().contains(QCursor::pos()))return;
        }
        else
        {
            if(!this->isHidden() && !this->geometry().contains(QCursor::pos()))
                this->hide();
        }
    }
}

void TrayView::OnBtnAddClicked()
{
    this->view->EditTaskInfo(TaskEditDialog::create);
}

void TrayView::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(palette().color(QPalette::Window));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), 15, 15);

    QWidget::paintEvent(paintEvent);
}

bool TrayView::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::Enter)
    {
        if(obj == label1)
        {
            // sLayout->setCurrentIndex(1);
            sLayout->setCurrentIndex(0);
            // view->ShowByDate(QDate::currentDate().addDays(1));
            view->ShowAll();
        }
        else if(obj == label2)
        {
            sLayout->setCurrentIndex(0);
            view->ShowByDate(QDate::currentDate().addDays(1));

        }
        else if(obj == label3)
        {
            sLayout->setCurrentIndex(0);
            view->ShowByDate(QDate::currentDate());
        }
    }
    return QObject::eventFilter(obj, event);
}
