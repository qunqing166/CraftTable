#ifndef COUNTDOWNDAYINFO_H
#define COUNTDOWNDAYINFO_H

#include "BaseInfo.h"

class CountdownDayInfo: public BaseInfo
{
public:
    // CountdownDayInfo();
    CountdownDayInfo(const QString&, const QDateTime&);
    CountdownDayInfo(const QJsonObject&);

    virtual QString Content() const override;
    virtual QString Type() const override;
    virtual QString Time() const override;
    virtual void FromJson(const QJsonObject &) override;
    virtual bool IsTimeout() const override;

    static const QString type;

private:
    QString content;
    QDateTime time;
};

#endif // COUNTDOWNDAYINFO_H
