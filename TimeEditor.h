#ifndef TIMEEDITOR_H
#define TIMEEDITOR_H

#include<QWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QMouseEvent>
#include<QPainter>
#include<QPropertyAnimation>
#include<QTimer>
#include<QDateTime>
#include<QPoint>
#include<QLabel>
#include<QPushButton>
#include<QObject>
#include<QStackedLayout>

class NumSelector : public QWidget
{
    Q_OBJECT


public:
    explicit NumSelector(QWidget *parent = nullptr);

    enum InforType
    {
        year,
        month,
        day,
        hour,
        minute,
        seconds,
        monthDayWeek,
        lunar
    };

    void SetNumType(const InforType &type){currentType = type;}
    void SetIsShowBackgroundRect(bool is){isShowBackgroundRect = is;}
    void SetCurrentDt(const QDateTime &dt);


protected:
    void paintEvent(QPaintEvent * event) override;
    void wheelEvent(QWheelEvent *event) override;


private:

    void OPenScaleTimer();
    void PaintAnimaStop(QPainter *painter);
    void PaintAnimaWork(QPainter *painter);
    void GetCurrentInfor();
    void TextFontInit();
    void InforExchange(bool isNext);
    void InforChange(bool isNext);

    int crtMovePos = 0;
    bool isAnimaStart = false;

    int crtTextFontsize = 16;
    int nextTextFontSize = 12;
    int lastTextFontSize = 12;

    int animaPlayerTime = 5;

    int moveStep = 5;
    int interval;

    bool isShowBackgroundRect = false;

    int textFontSizeMax = 16;
    int textFontSizeMin = 12;

    QFont crtTextFont;
    QFont lastTextFont;
    QFont nextTextFont;

    //控制缩放的定时器
    QTimer *scaleTimer;

    QString currentInfor;
    QString lastInfor;
    QString nextInfor;

    InforType currentType = InforType::month;
    QDateTime currentDt = QDateTime::currentDateTime();

signals:
    void CurrentInforChange(QDateTime dt, InforType type);

};

class TimeEditor:public QWidget
{
    Q_OBJECT

    QDateTime currentDt = QDateTime::currentDateTime();
    QLabel *crtInforLabel;// = new QLabel(this);
    int index = 0;          //使用编号
    int type = 0;           //编辑格式
    QStackedLayout *stackedLayout;// = new QStackedLayout(this);

public:
    TimeEditor(QWidget *parent = nullptr);
    void SetIndex(const int &index1){index = index1;}
    void SetType(const int &type1);
    void ShowReset(const QDateTime &dt);
    QDateTime GetDateTime();
    QString GetTimeStr();

    static QString GetDayOfWeek(int day);

private:
    void UpdateCurrenInfor(QDateTime dt, NumSelector::InforType type);

    void DtEditInit();
    void TimeEditInit();
    void DateEditInit();

signals:
    void Cancel();
    void OK(int index, QDateTime dt);
};

#endif // TIMEEDITOR_H
