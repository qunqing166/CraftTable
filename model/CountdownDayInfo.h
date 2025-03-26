#ifndef COUNTDOWNDAYINFO_H
#define COUNTDOWNDAYINFO_H

#include "BaseInfo.h"

class CountdownDayInfo: public BaseInfo
{
public:
    CountdownDayInfo(const QString&, const QDate&);
    CountdownDayInfo(const QJsonObject&);
    ~CountdownDayInfo(){}

    virtual QString Content() const override;
    virtual QString Time() const override;
    virtual QJsonObject ToJson() const override;
    virtual void FromJson(const QJsonObject &) override;
    virtual bool IsTimeout() const override;
    bool IsShowByDate(const QDateTime &dt) const override;

    QDate GetTime() const {return time;}

private:
    // QString content;
    QDate time;

};

#endif // COUNTDOWNDAYINFO_H
