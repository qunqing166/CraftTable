#include "DailyTask.h"

DailyTask::DailyTask(const QString &content, const QDate &start, const QDate& end):
    BaseInfo(Model::daily_task, content), start(start), end(end)
{

}

DailyTask::DailyTask(const QJsonObject &obj):
    BaseInfo(Model::daily_task)
{
    FromJson(obj);
}

QString DailyTask::Time() const
{
    int days = QDate::currentDate().daysTo(start);
    return QString("%1~%2 | %3").arg(start.toString("MM-dd"))
                                .arg(end.toString("MM-dd"))
                                .arg((days > 0) ? QString("%1日后").arg(days) : QString("累计%1天").arg(-days));
}

bool DailyTask::IsTimeout() const
{
    return end < QDate::currentDate();
}

bool DailyTask::IsShowByDate(const QDateTime &dt) const
{
    return dt.date() >= start;
}

void DailyTask::FromJson(const QJsonObject &obj)
{
    this->content = obj["content"].toString();
    this->start = QDate::fromString(obj["time"].toObject()["start"].toString());
    this->end = QDate::fromString(obj["time"].toObject()["end"].toString());
    if (obj["is_complete"].toBool())
        this->Completed();
}

QJsonObject DailyTask::ToJson() const
{
    return QJsonObject{ {"content", Content()},
                        {"type", Model::TypeToStr.value(Model::TypeToChinese.key(Type()))},
                        {"time", QJsonObject{{"start", start.toString()}, {"end", end.toString()}}},
                        {"is_complete", this->IsCompleted()}};
}
