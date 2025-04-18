#include "AbstractDataSelector.h"
#include <QEnterEvent>
#include <QPainter>

AbstractDataSelector::AbstractDataSelector(QWidget *parent):
    QWidget(parent)
{

    /**
     * 在这里有个问题, 由于基类先于其他数据初始化
     * 当基类的构造函数加载数据到label时, 无法获取正确数据
     * 这时候需要在派生类的初始化函数中调用'UpdateText()'来刷新数据
     */

    labelCrt = new QLabel(CurrentData(), this);
    labelNext = new QLabel(NextData(), this);
    labelLast = new QLabel(LastData(), this);

    labelCrt->setAlignment(Qt::AlignCenter);
    labelNext->setAlignment(Qt::AlignCenter);
    labelLast->setAlignment(Qt::AlignCenter);

    // labelLast->setStyleSheet("background-color:transparent;");
    // labelCrt->setStyleSheet("background-color:transparent;");
    // labelNext->setStyleSheet("background-color:transparent;");

    line1 = new QFrame(this);
    line2 = new QFrame(this);

    animaDy = new QPropertyAnimation(this, "Dy", this);
    animaDy->setDuration(100);

    SetBackgroundColor(Qt::white);
    SetLineColor(Qt::black);
    SetTextColor(Qt::black);

    // this->setFixedSize(200, 200);
    // this->setMinimumSize(60, 150);

    // connect(animaDy, &QPropertyAnimation::stateChanged, this, [&](){
    //     qDebug() << "state";
    // });
    // connect(animaDy, &QPropertyAnimation::finished, this, [&](){
    //     // qDebug() << "anima finished";
    // });
    connect(animaDy, &QPropertyAnimation::valueChanged, this, [&](){
        this->update();
    });
}

void AbstractDataSelector::SetBackgroundColor(const QColor &color)
{
    this->setStyleSheet(QString("background-color:%1;").arg(color.name()));
}

void AbstractDataSelector::SetTextColor(const QColor &color)
{
    QPalette pal = labelLast->palette();
    pal.setColor(QPalette::WindowText, color);
    labelLast->setPalette(pal);
    labelCrt->setPalette(pal);
    labelNext->setPalette(pal);
}

void AbstractDataSelector::SetLineColor(const QColor &color)
{
    QString style = QString("background-color:%1;").arg(color.name());
    line1->setStyleSheet(style);
    line2->setStyleSheet(style);
}

// QString AbstractDataSelector::CurrentData(){ return QString::number(crtInt); }
// QString AbstractDataSelector::NextData() { return QString::number(crtInt + 1); }
// QString AbstractDataSelector::LastData() { return QString::number(crtInt - 1); }

void AbstractDataSelector::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y() > 0)
    {
        if(!IsLastable())return;
        isNext = false;
        animaDy->setStartValue(0);
        qDebug() << this->height();
        animaDy->setEndValue(this->height() / 3);
    }
    else
    {
        if(!IsNextable())return;
        animaDy->setStartValue(0);
        qDebug() << this->height();
        animaDy->setEndValue(-this->height() / 3);
        isNext = true;
    }

    isDyHalf = false;
    UpdateText();
    animaDy->start();
}

void AbstractDataSelector::UpdateText()
{
    labelLast->setText(LastData());
    labelCrt->setText(CurrentData());
    labelNext->setText(NextData());
}

void AbstractDataSelector::paintEvent(QPaintEvent *event)
{
    if(isDyHalf == false && abs(dy) > (this->height() / 6))
    {
        isDyHalf = true;
        ChangeData(isNext);
        if(isNext)
        {
            labelLast->setText(NextData());
        }
        else
        {
            labelNext->setText(LastData());
        }
    }

    labelLast->resize(this->width(), this->height() / 3 + 6);
    labelCrt->resize(this->width(), this->height() / 3);
    labelNext->resize(this->width(), this->height() / 3);

    if(isNext == true && isDyHalf)
    {
        labelLast->move(0, this->height() + dy - 6);
    }
    else
    {
        labelLast->move(0, 0 + dy);
    }


    labelCrt->move(0, this->height() / 3 + dy);


    if(isNext == false && isDyHalf)
    {
        labelNext->move(0, dy - this->height() / 3);
    }
    else
    {
        labelNext->move(0, this->height() / 3 * 2 + dy);
    }

    line1->resize(this->width(), 2);
    line2->resize(this->width(), 2);

    line1->move(0, this->height() / 3 + this->height() / 12);
    line2->move(0, this->height() / 3 * 2 - this->height() / 12);
}
void AbstractDataSelector::SetDy(int d)
{
    dy = d;
}

int AbstractDataSelector::Dy() const
{
    return dy;
}
