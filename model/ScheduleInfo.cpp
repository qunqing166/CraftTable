#include "ScheduleInfo.h"

ScheduleInfo::ScheduleInfo(const QString &content, const QDateTime &s, const QDateTime &e):
    content(content), start(s), end(e), BaseInfo(Model::schedule)
{

}

ScheduleInfo::ScheduleInfo(const QJsonObject &obj):
    BaseInfo(Model::schedule)
{
    FromJson(obj);
}

QString ScheduleInfo::Content() const
{
    return content;
}

QString ScheduleInfo::Time() const
{
    return QString("%1月%2日 %3:%4-%5:%6")
        .arg(start.date().month())
        .arg(start.date().day())
        .arg(start.time().hour())
        .arg(start.time().minute())
        .arg(end.time().hour())
        .arg(end.time().minute());
    // return start.time().toString() + "to" + end.time().toString();
}

QJsonObject ScheduleInfo::ToJson() const
{
    QJsonObject obj;
    obj.insert("content", this->Content());
    obj.insert("type", Model::TypeToStr.value(Model::TypeToChinese.key(Type())));
    obj.insert("time", QJsonObject{{"start", start.toString()}, {"end", end.toString()}});
    return obj;
}

void ScheduleInfo::FromJson(const QJsonObject &obj)
{
    this->content = obj["content"].toString();
    QString time = obj["time"].toString();
    start = QDateTime::fromString(obj["time"].toObject()["start"].toString());
    end = QDateTime::fromString(obj["time"].toObject()["end"].toString());
}

bool ScheduleInfo::IsTimeout() const
{
    return end.date() < QDate::currentDate();
}
