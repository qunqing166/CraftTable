#include "TimeEditor.h"

TimeEditor::TimeEditor(QWidget *parent):
    QWidget(parent)
{
    //兼容样式表
    this->setAttribute(Qt::WA_StyledBackground);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);

    QVBoxLayout *mainVLayout = new QVBoxLayout(this);
    this->setLayout(mainVLayout);

    crtInforLabel = new QLabel(this);
    crtInforLabel->setAlignment(Qt::AlignCenter);
    crtInforLabel->setObjectName("crtInforLabel");
    stackedLayout = new QStackedLayout(this);
    //初始化三种不同的编辑器样式
    DtEditInit();
    TimeEditInit();
    DateEditInit();

    // ShowReset(QDateTime::currentDateTime());
    mainVLayout->addWidget(crtInforLabel, 1);
    mainVLayout->addLayout(stackedLayout, 5);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    mainVLayout->addLayout(hLayout1);

    // QPushButton *pb1 = new QPushButton("取消", this);
    // QPushButton *pb2 = new QPushButton("确定", this);
    // pb1->setObjectName("dtEditor_pb");
    // pb2->setObjectName("dtEditor_pb");
    // QHBoxLayout *hLayout2 = new QHBoxLayout(this);
    // hLayout2->addWidget(pb1);
    // hLayout2->addWidget(pb2);

    // mainVLayout->addLayout(hLayout2);

    // ShowReset(QDateTime::currentDateTime());

    // connect(pb1, &QPushButton::clicked, this, [&](){
    //     emit Cancel();
    // });
    // connect(pb2, &QPushButton::clicked, this, [&](){
    //     emit OK(index, currentDt);
    // });
}

void TimeEditor::UpdateCurrenInfor(QDateTime dt, NumSelector::InforType type)
{
    //更新显示数据
    if(type == NumSelector::InforType::year)
        currentDt.setDate(QDate(dt.date().year(), currentDt.date().month(), currentDt.date().day()));
    else if(type == NumSelector::InforType::month)
        currentDt.setDate(QDate(currentDt.date().year(), dt.date().month(), currentDt.date().day()));
    else if(type == NumSelector::InforType::day)
        currentDt.setDate(QDate(currentDt.date().year(), currentDt.date().month(), dt.date().day()));
    else if(type == NumSelector::InforType::hour)
        currentDt.setTime(QTime(dt.time().hour(), currentDt.time().minute()));
    else if(type == NumSelector::InforType::minute)
        currentDt.setTime(QTime(currentDt.time().hour(), dt.time().minute()));
    else if(type == NumSelector::InforType::monthDayWeek)
        currentDt.setDate(QDate(dt.date().year(), dt.date().month(), dt.date().day()));
    QString str = QString::asprintf("%d年%d月%d日 %s %d时%d分", currentDt.date().year(), currentDt.date().month(), currentDt.date().day(), GetDayOfWeek(currentDt.date().dayOfWeek()).toStdString().c_str(), currentDt.time().hour(), currentDt.time().minute());
    crtInforLabel->setText(str);
}

QString TimeEditor::GetDayOfWeek(int day)
{
    QString ret;
    switch(day % 7)
    {
    case 0:ret = "周日";break;
    case 1:ret = "周一";break;
    case 2:ret = "周二";break;
    case 3:ret = "周三";break;
    case 4:ret = "周四";break;
    case 5:ret = "周五";break;
    case 6:ret = "周六";break;
    }
    return ret;
}

void TimeEditor::DtEditInit()
{
    //日, 时, 分编辑
    QWidget *widget = new QWidget(this);
    stackedLayout->addWidget(widget);
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    widget->setLayout(hLayout);
    NumSelector *day = new NumSelector(this);
    day->SetNumType(NumSelector::InforType::monthDayWeek);
    NumSelector *hour = new NumSelector(this);
    hour->SetNumType(NumSelector::InforType::hour);
    NumSelector *minute = new NumSelector(this);
    minute->SetNumType(NumSelector::InforType::minute);
    hLayout->addWidget(day, 2);
    hLayout->addWidget(hour, 1);
    hLayout->addWidget(minute, 1);

    connect(day, &NumSelector::CurrentInforChange, this, &TimeEditor::UpdateCurrenInfor);
    connect(hour, &NumSelector::CurrentInforChange, this, &TimeEditor::UpdateCurrenInfor);
    connect(minute, &NumSelector::CurrentInforChange, this, &TimeEditor::UpdateCurrenInfor);
}

void TimeEditor::TimeEditInit()
{
    //时, 分编辑
    QWidget *widget = new QWidget(this);
    stackedLayout->addWidget(widget);
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    widget->setLayout(hLayout);
    NumSelector *hour = new NumSelector(this);
    hour->SetNumType(NumSelector::InforType::hour);
    NumSelector *minute = new NumSelector(this);
    minute->SetNumType(NumSelector::InforType::minute);
    hLayout->addWidget(hour);
    hLayout->addWidget(minute);

    connect(hour, &NumSelector::CurrentInforChange, this, &TimeEditor::UpdateCurrenInfor);
    connect(minute, &NumSelector::CurrentInforChange, this, &TimeEditor::UpdateCurrenInfor);
}

void TimeEditor::DateEditInit()
{
    //年, 月, 日编辑
    QWidget *widget = new QWidget(this);
    stackedLayout->addWidget(widget);
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    widget->setLayout(hLayout);
    NumSelector *year = new NumSelector(this);
    year->SetNumType(NumSelector::InforType::year);
    NumSelector *month = new NumSelector(this);
    month->SetNumType(NumSelector::InforType::month);
    NumSelector *day = new NumSelector(this);
    day->SetNumType(NumSelector::InforType::day);
    hLayout->addWidget(year);
    hLayout->addWidget(month);
    hLayout->addWidget(day);

    connect(year, &NumSelector::CurrentInforChange, this, &TimeEditor::UpdateCurrenInfor);
    connect(month, &NumSelector::CurrentInforChange, this, &TimeEditor::UpdateCurrenInfor);
    connect(day, &NumSelector::CurrentInforChange, this, &TimeEditor::UpdateCurrenInfor);
}

void TimeEditor::ShowReset(const QDateTime &dt)
{
    QString str = QString::asprintf("%d年%d月%d日 %s %d时%d分", dt.date().year(), dt.date().month(), dt.date().day(), GetDayOfWeek(dt.date().dayOfWeek()).toStdString().c_str(), dt.time().hour(), dt.time().minute());
    crtInforLabel->setText(str);
    currentDt = dt;

}

QDateTime TimeEditor::GetDateTime()
{
    return this->currentDt;
}

QString TimeEditor::GetTimeStr()
{
    return crtInforLabel->text();
}



NumSelector::NumSelector(QWidget *parent):
    QWidget(parent)
{
    scaleTimer = new QTimer(this);
    currentType = InforType::day;


    connect(scaleTimer, &QTimer::timeout, this, [&](){
        crtMovePos += moveStep;

        int crtMovePosAbs = abs(crtMovePos);

        if(crtMovePosAbs > interval)
        {
            scaleTimer->stop();
            crtMovePos = 0;
            isAnimaStart = false;

            if(moveStep > 0)
            {
                InforChange(false);
            }
            else
            {
                InforChange(true);
            }
        }

        this->repaint();
    });
}

void NumSelector::SetCurrentDt(const QDateTime &dt)
{
    currentDt = dt;
}

void NumSelector::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(isAnimaStart)
    {
        PaintAnimaWork(&painter);
    }
    else
    {
        PaintAnimaStop(&painter);
    }
}

void NumSelector::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y() < 0)
    {
        moveStep = -1;

    }
    else
    {
        moveStep = 1;
    }
    OPenScaleTimer();
    isAnimaStart = true;
}

void NumSelector::OPenScaleTimer()
{
    interval = this->height() / 5;
    scaleTimer->start(animaPlayerTime);
}

void NumSelector::PaintAnimaStop(QPainter *painter)
{
    int width = this->width();
    int height = this->height() / 5;

    QPoint crtPos(0, this->height() / 2 - height / 2);

    QPoint lastPos(0, crtPos.y() - height);

    QPoint nextPos(0, crtPos.y() + height);

    QRect rect1(crtPos, QSize(width, height));
    QRect rect2(lastPos, QSize(width, height));
    QRect rect3(nextPos, QSize(width, height));

    GetCurrentInfor();

    painter->setBrush(Qt::red);
    if(isShowBackgroundRect)
    {
        painter->drawRect(rect1);
        painter->drawRect(rect2);
        painter->drawRect(rect3);
    }

    crtTextFont = QFont("宋体", 10, QFont::Bold, true);

    crtTextFont.setPixelSize(textFontSizeMax);
    painter->setFont(crtTextFont);
    painter->drawText(rect1, Qt::AlignHCenter, currentInfor);

    QColor textColor(Qt::black);
    textColor.setAlpha(120);

    painter->setPen(textColor);
    crtTextFont.setPixelSize(textFontSizeMin);
    painter->setFont(crtTextFont);
    painter->drawText(rect2, Qt::AlignHCenter, lastInfor);
    crtTextFont.setPixelSize(nextTextFontSize);
    painter->setFont(crtTextFont);
    painter->drawText(rect3, Qt::AlignHCenter, nextInfor);
}

void NumSelector::PaintAnimaWork(QPainter *painter)
{
    int width = this->width();
    int height = this->height() / 5;

    GetCurrentInfor();

    QPoint crtPos(0, this->height() / 2 - height / 2 + crtMovePos);

    QPoint lastPos;
    QPoint nextPos;
    if(crtMovePos > interval / 2)
    {
        lastPos = QPoint(0, crtPos.y() - height);
        nextPos = QPoint(0, lastPos.y() - height);
        InforExchange(true);
    }
    else if(-crtMovePos > interval / 2)
    {
        nextPos = QPoint(0, crtPos.y() + height);
        lastPos = QPoint(0, nextPos.y() + height);
        InforExchange(false);
    }
    else
    {
        lastPos = QPoint(0, crtPos.y() - height);
        nextPos = QPoint(0, crtPos.y() + height);
    }


    QRect rect1(crtPos, QSize(width, height));
    QRect rect2(lastPos, QSize(width, height));
    QRect rect3(nextPos, QSize(width, height));

    painter->setBrush(Qt::red);
    if(isShowBackgroundRect)
    {
        painter->drawRect(rect1);
        painter->drawRect(rect2);
        painter->drawRect(rect3);
    }

    QColor textColor(Qt::black);
    textColor.setAlpha(255 - abs((this->height() / 2 - rect1.center().y())) * 2);
    painter->setPen(textColor);
    crtTextFont.setPixelSize(textFontSizeMax - abs(this->height() / 2 - rect1.center().y()) * 1.0 / interval * (textFontSizeMax - textFontSizeMin));
    painter->setFont(crtTextFont);
    painter->drawText(rect1, Qt::AlignHCenter, currentInfor);

    crtTextFont.setPixelSize(textFontSizeMax - abs(this->height() / 2 - rect2.center().y()) * 1.0 / interval * (textFontSizeMax - textFontSizeMin));
    textColor.setAlpha(255 - abs((this->height() / 2 - rect2.center().y())) * 2);
    painter->setPen(textColor);
    painter->setFont(crtTextFont);
    painter->drawText(rect2, Qt::AlignHCenter, lastInfor);

    textColor.setAlpha(255 - abs((this->height() / 2 - rect3.center().y())) * 2);
    painter->setPen(textColor);
    crtTextFont.setPixelSize(textFontSizeMax - abs(this->height() / 2 - rect3.center().y()) * 1.0 / interval * (textFontSizeMax - textFontSizeMin));
    painter->setFont(crtTextFont);
    painter->drawText(rect3, Qt::AlignHCenter, nextInfor);
}

void NumSelector::GetCurrentInfor()
{
    if(currentType == InforType::monthDayWeek)
    {
        QDate date = currentDt.date();
        currentInfor = QString::asprintf("%d 月 %d 日", date.month(), date.day());
        lastInfor = QString::asprintf("%d 月 %d 日", date.addDays(-1).month(), date.addDays(-1).day());
        nextInfor = QString::asprintf("%d 月 %d 日", date.addDays(1).month(), date.addDays(1).day());
    }
    else if(currentType == InforType::hour)
    {
        int hour = currentDt.time().hour();
        currentInfor = QString::asprintf("%02d时", hour);
        nextInfor = QString::asprintf("%02d时", (hour + 1) % 24);
        lastInfor = QString::asprintf("%02d时", (hour + 23) % 24);
    }
    else if(currentType == InforType::minute)
    {
        int minute = currentDt.time().minute();
        currentInfor = QString::asprintf("%02d分", minute);
        nextInfor = QString::asprintf("%02d分", (minute + 1) % 60);
        lastInfor = QString::asprintf("%02d分", (minute + 59) % 60);
    }
    else if(currentType == InforType::year)
    {
        currentInfor = QString::asprintf("%04d年", currentDt.date().year());
        nextInfor = QString::asprintf("%04d年", currentDt.date().addYears(1).year());
        lastInfor = QString::asprintf("%04d年", currentDt.date().addYears(-1).year());
    }
    else if(currentType == InforType::month)
    {
        currentInfor = QString::asprintf("%02d月", currentDt.date().month());
        nextInfor = QString::asprintf("%02d月", currentDt.date().addMonths(1).month());
        lastInfor = QString::asprintf("%02d月", currentDt.date().addMonths(-1).month());
    }
    else if(currentType == InforType::day)
    {
        currentInfor = QString::asprintf("%d日", currentDt.date().day());
        nextInfor = QString::asprintf("%d日", currentDt.date().addDays(1).day());
        lastInfor = QString::asprintf("%d日", currentDt.date().addDays(-1).day());
    }
}

void NumSelector::TextFontInit()
{
    crtTextFont = QFont("宋体", crtTextFontsize, QFont::Bold, true);
    nextTextFont = QFont("宋体", nextTextFontSize, QFont::Bold, true);
    lastTextFont = QFont("宋体", lastTextFontSize, QFont::Bold, true);
}

void NumSelector::InforExchange(bool isNext)
{
    if(isNext)
    {
        if(currentType == InforType::monthDayWeek)
            nextInfor = QString::asprintf("%d 月 %d 日", currentDt.addDays(-2).date().month(), currentDt.addDays(-2).date().day());
        else if(currentType == InforType::minute)
            nextInfor = QString::asprintf("%02d分", (currentDt.time().minute() + 58) % 60);
        else if(currentType == InforType::hour)
            nextInfor = QString::asprintf("%02d时", (currentDt.time().hour() + 22) % 24);
        else if(currentType == InforType::year)
            nextInfor = QString::asprintf("%d年", currentDt.date().addYears(-2).year());
        else if(currentType == InforType::month)
            nextInfor = QString::asprintf("%02d月", currentDt.date().addMonths(-2).month());
        else if(currentType == InforType::day)
            nextInfor = QString::asprintf("%02d日", currentDt.date().addDays(-2).day());
    }
    else
    {
        if(currentType == InforType::monthDayWeek)
            lastInfor = QString::asprintf("%d 月 %d 日", currentDt.addDays(2).date().month(), currentDt.addDays(2).date().day());
        else if(currentType == InforType::minute)
            lastInfor = QString::asprintf("%02d分", (currentDt.time().minute() + 2) % 60);
        else if(currentType == InforType::hour)
            lastInfor = QString::asprintf("%02d时", (currentDt.time().hour() + 2) % 24);
        else if(currentType == InforType::year)
            lastInfor = QString::asprintf("%d年", currentDt.date().addYears(2).year());
        else if(currentType == InforType::month)
            lastInfor = QString::asprintf("%02d月", currentDt.date().addMonths(2).month());
        else if(currentType == InforType::day)
            lastInfor = QString::asprintf("%02d日", currentDt.date().addDays(2).day());
    }
}

void NumSelector::InforChange(bool isNext)
{
    if(isNext)
    {
        if(currentType == InforType::monthDayWeek)
            currentDt = currentDt.addDays(1);
        else if(currentType == InforType::hour)
            currentDt = currentDt.addSecs(60 * 60);
        else if(currentType == InforType::minute)
            currentDt = currentDt.addSecs(60);
        else if(currentType == InforType::year)
            currentDt = currentDt.addYears(1);
        else if(currentType == InforType::month)
            currentDt = currentDt.addMonths(1);
        else if(currentType == InforType::day)
            currentDt = currentDt.addDays(1);
    }
    else
    {
        if(currentType == InforType::monthDayWeek)
            currentDt = currentDt.addDays(-1);
        else if(currentType == InforType::hour)
            currentDt = currentDt.addSecs(-60 * 60);
        else if(currentType == InforType::minute)
            currentDt = currentDt.addSecs(-60);
        else if(currentType == InforType::year)
            currentDt = currentDt.addYears(-1);
        else if(currentType == InforType::month)
            currentDt = currentDt.addMonths(-1);
        else if(currentType == InforType::day)
            currentDt = currentDt.addDays(-1);
    }
    emit CurrentInforChange(currentDt, currentType);
}

void TimeEditor::SetType(const int &type1)
{
    type = type1;
    stackedLayout->setCurrentIndex(type);
}
