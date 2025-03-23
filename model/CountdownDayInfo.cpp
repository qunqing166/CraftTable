#include "CountdownDayInfo.h"

const QString CountdownDayInfo::type = "countdown_day";

// CountdownDayInfo::CountdownDayInfo() {}

CountdownDayInfo::CountdownDayInfo(const QString &content, const QDateTime &dt):
    content(content), time(dt)
{

}

CountdownDayInfo::CountdownDayInfo(const QJsonObject &obj)
{
    FromJson(obj);
}

bool CountdownDayInfo::IsTimeout() const
{
    return time.date() < QDate::currentDate();
}

QString CountdownDayInfo::Content() const
{
    return content;
}

QString CountdownDayInfo::Type() const
{
    // return "countdown_day";
    return CountdownDayInfo::type;
}

QString CountdownDayInfo::Time() const
{
    return time.toString();
}

void CountdownDayInfo::FromJson(const QJsonObject &obj)
{
    this->content = obj["content"].toString();
    this->time = QDateTime::fromString(obj["time"].toString());
}
