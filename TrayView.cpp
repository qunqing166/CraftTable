#include "TaskView.h"
#include "TrayView.h"
#include <QMenu>
#include <QAction>
#include <QCursor>
#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QEvent>

TrayView::TrayView(QWidget *parent):QWidget(nullptr)
{
    this->setFixedSize(250, 500);
    ObjectInit();
    WidgetInit();
}

void TrayView::ObjectInit()
{
    trayIcon = new QSystemTrayIcon(this);
    hoverCheckTimer = new QTimer(this);
    trayIcon->setIcon(QIcon("C:\\Users\\qunqing\\Desktop\\图片\\新建文件夹 (2)\\hj.png"));

    QMenu *trayMenu = new QMenu(this);
    QAction *restoreAction = new QAction("Restore", this);
    QAction *quitAction = new QAction("Quit", this);

    trayMenu->addAction(restoreAction);
    trayMenu->addAction(quitAction);

    connect(restoreAction, &QAction::triggered, this, &TrayView::showNormal);
    connect(quitAction, &QAction::triggered, this, &TrayView::close);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();


    hoverCheckTimer->start(20);
    connect(hoverCheckTimer, &QTimer::timeout, this, &TrayView::CheckTrayIconMouseHover);
}

void TrayView::WidgetInit()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_StyledBackground);

    setStyleSheet(R"(
                TrayView{
                    background: white;
                    border-radius: 15px;
                    border: 4px solid #333;
                }
    )");

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setAlignment(Qt::AlignTop);
    vLayout->setContentsMargins(4, 4, 4, 4);
    this->setLayout(vLayout);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->setAlignment(Qt::AlignLeft);
    vLayout->addLayout(hLayout);

    QLabel *labelDate = new QLabel("3/17 ", this);
    QLabel *labelWeekday = new QLabel("周一", this);
    QPushButton *btnAdd = new QPushButton(this);

    labelDate->setStyleSheet(R"(
                background-color: white;
                color:black;
                font-size:20px;
                font-family:KaiTi;
    )");
    labelWeekday->setStyleSheet(R"(
                background-color: white;
                color:#18b8f7;
                font-size:12px;
                font-family:KaiTi;
    )");
    hLayout->addWidget(labelDate);
    hLayout->addWidget(labelWeekday);
    QLabel *labelEmpty = new QLabel(this);
    labelEmpty->setFixedWidth(80);
    hLayout->addWidget(labelEmpty);
    hLayout->addWidget(btnAdd);
    sLayout = new QStackedLayout(this);
    vLayout->addLayout(sLayout);

    TaskView *view = new TaskView(this);
    sLayout->addWidget(view);
    QWidget *widget = new QWidget(this);
    sLayout->addWidget(widget);
    sLayout->setCurrentIndex(0);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    vLayout->addLayout(hLayout1);

    label1 = new QLabel("1", this);
    label2 = new QLabel("2", this);
    hLayout1->addWidget(label1);
    hLayout1->addWidget(label2);

    label1->installEventFilter(this);
    label2->installEventFilter(this);
}

void TrayView::CheckTrayIconMouseHover()
{
    static QTimer timer;
    connect(&timer, &QTimer::timeout, &timer, &QTimer::stop);
    if(trayIcon->geometry().contains(QCursor::pos()))
    {
        this->move(trayIcon->geometry().topLeft() - QPoint(this->width() / 3 * 2, this->height()));
        this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
        this->show();
        timer.start(200);
    }
    else
    {
        if(timer.isActive())
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

void TrayView::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 使用样式表定义的颜色
    painter.setBrush(palette().color(QPalette::Window));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), 15, 15);
}

bool TrayView::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::Enter)
    {

        if(obj == label1)
        {
            sLayout->setCurrentIndex(1);
        }
        else if(obj == label2)
        {
            sLayout->setCurrentIndex(0);
        }
    }

    return QObject::eventFilter(obj, event);
}
