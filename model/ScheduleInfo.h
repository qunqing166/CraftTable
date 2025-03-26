#ifndef SCHEDULEINFO_H
#define SCHEDULEINFO_H

#include "BaseInfo.h"
#include <QDateTime>

class ScheduleInfo: public BaseInfo
{
public:
    ScheduleInfo(const QString&, const QDateTime&, const QDateTime&);
    ScheduleInfo(const QJsonObject&);
    ~ScheduleInfo(){}

    virtual QString Content() const override;
    virtual QString Time() const override;
    virtual QJsonObject ToJson() const override;
    virtual void FromJson(const QJsonObject &) override;

    virtual bool IsTimeout() const override;

    QDateTime GetSTime() const {return start;}
    QDateTime GetETime() const {return end;}

private:

    // QString content;
    QDateTime start = QDateTime::currentDateTime();
    QDateTime end = QDateTime::currentDateTime();
};

#endif // SCHEDULEINFO_H
