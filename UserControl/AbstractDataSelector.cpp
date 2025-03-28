#include "AbstractDataSelector.h"
#include <QEnterEvent>
#include <QPainter>

AbstractDataSelector::AbstractDataSelector(QWidget *parent):
    QWidget(parent)
{

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

    this->setFixedSize(200, 200);

    connect(animaDy, &QPropertyAnimation::valueChanged, this, [&](){
        this->update();
    });
    connect(animaDy, &QPropertyAnimation::finished, this, [&](){

    });

    this->repaint();
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
        isNext = false;
        animaDy->setStartValue(0);
        animaDy->setEndValue(this->height() / 3);
    }
    else
    {
        animaDy->setStartValue(0);
        animaDy->setEndValue(-this->height() / 3);
        isNext = true;
    }

    isDyHalf = false;
    labelLast->setText(LastData());
    labelCrt->setText(CurrentData());
    labelNext->setText(NextData());
    animaDy->start();
}

// void AbstractDataSelector::ChangeData(bool isNext) {
//     if (isNext)crtInt++;
//     else crtInt--;
// }

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
