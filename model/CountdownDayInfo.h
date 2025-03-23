#ifndef COUNTDOWNDAYINFO_H
#define COUNTDOWNDAYINFO_H

#include "BaseInfo.h"

class CountdownDayInfo: public BaseInfo
{
public:
    CountdownDayInfo(const QString&, const QDate&);
    CountdownDayInfo(const QJsonObject&);

    virtual QString Content() const override;
    virtual QString Time() const override;
    virtual QJsonObject ToJson() const override;
    virtual void FromJson(const QJsonObject &) override;
    virtual bool IsTimeout() const override;

private:
    QString content;
    QDate time;
};

#endif // COUNTDOWNDAYINFO_H
