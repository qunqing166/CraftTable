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
    // return QString("%1月%2日 %3:%4-%5:%6")
    //     .arg(start.date().month())
    //     .arg(start.date().day())
    //     .arg(start.time().hour())
    //     .arg(start.time().minute())
    //     .arg(end.time().hour())
    //     .arg(end.time().minute());
    return QString("%1-%2")
        .arg(start.toString("MM-dd  hh:mm"))
        .arg(end.toString("hh:mm"));
}

QJsonObject ScheduleInfo::ToJson() const
{
    QJsonObject obj;
    obj.insert("content", this->Content());
    obj.insert("type", Model::TypeToStr.value(Model::TypeToChinese.key(Type())));
    obj.insert("time", QJsonObject{{"start", start.toString()}, {"end", end.toString()}});
    obj.insert("is_complete", this->IsCompleted());
    return obj;
}

void ScheduleInfo::FromJson(const QJsonObject &obj)
{
    this->content = obj["content"].toString();
    QString time = obj["time"].toString();
    start = QDateTime::fromString(obj["time"].toObject()["start"].toString());
    end = QDateTime::fromString(obj["time"].toObject()["end"].toString());
    if(obj["is_complete"].toBool())this->Completed();
}

bool ScheduleInfo::IsTimeout() const
{
    return end.date() < QDate::currentDate();
}
