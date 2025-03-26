#include "CountdownDayInfo.h"
#include "../utility/Utility.h"
#include "ModelType.h"

CountdownDayInfo::CountdownDayInfo(const QString &con, const QDate &date):
    time(date), BaseInfo(Model::countdown_day, con)
{

}

CountdownDayInfo::CountdownDayInfo(const QJsonObject &obj):
    BaseInfo(Model::countdown_day)
{
    FromJson(obj);
}

bool CountdownDayInfo::IsTimeout() const
{
    return time < QDate::currentDate();
}

QString CountdownDayInfo::Content() const
{
    return content;
}

QString CountdownDayInfo::Time() const
{
    int days = QDate::currentDate().daysTo(time);
    // return QString("%1年%2月%3日 %4 | %5")
    //     .arg(time.year())
    //     .arg(time.month())
    //     .arg(time.day())
    //     .arg(Utility::GetDayOfWeek(time.dayOfWeek()))
    //     .arg(days == 0 ? QString("今日") : QString("剩余%1日").arg(days));
    return QString("%1 %2 | %3")
        .arg(time.toString("yyyy:MM:dd"))
        .arg(Utility::GetDayOfWeek(time.dayOfWeek()))
        .arg(days == 0 ? QString("今日") : QString("剩余%1日").arg(days));
}

QJsonObject CountdownDayInfo::ToJson() const
{
    return QJsonObject{{"content", Content()},
                       {"type", Model::TypeToStr.value(Model::TypeToChinese.key(Type()))},
                       {"time", time.toString()},
                       {"is_complete", this->IsCompleted()}};
}

void CountdownDayInfo::FromJson(const QJsonObject &obj)
{
    this->content = obj["content"].toString();
    this->time = QDate::fromString(obj["time"].toString());
    if(obj["is_complete"].toBool())this->Completed();
}
