#ifndef SCHEDULEINFO_H
#define SCHEDULEINFO_H

#include "BaseInfo.h"
#include <QDateTime>

class ScheduleInfo: public BaseInfo
{
public:
    // ScheduleInfo();
    ScheduleInfo(const QString&, const QDateTime&, const QDateTime&);
    ScheduleInfo(const QJsonObject&);

    // BaseInfo interface
    virtual QString Content() const override;
    virtual QString Type() const override;
    virtual QString Time() const override;
    virtual QJsonObject ToJson() const override;
    virtual void FromJson(const QJsonObject &) override;

    virtual bool IsTimeout() const override;

    static const QString type;

private:

    QString content;
    QDateTime start = QDateTime::currentDateTime();
    QDateTime end = QDateTime::currentDateTime();
};

#endif // SCHEDULEINFO_H
