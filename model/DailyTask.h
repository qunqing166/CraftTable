#ifndef DAILYTASK_H
#define DAILYTASK_H

#include "BaseInfo.h"
#include <QDate>

class DailyTask: public BaseInfo
{
public:
    DailyTask(const QString&, const QDate&, const QDate&);
    DailyTask(const QJsonObject&);

    QString Time() const;
    bool IsTimeout() const;
    bool IsShowByDate(const QDateTime &dt) const;
    void FromJson(const QJsonObject &);
    QJsonObject ToJson() const;

    QDateTime GetSTime() const {return QDateTime(start, QTime());}
    QDateTime GetETime() const {return QDateTime(end, QTime());}

private:
    QDate start;
    QDate end;

};

#endif // DAILYTASK_H
