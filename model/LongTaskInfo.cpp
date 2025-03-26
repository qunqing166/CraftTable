#include "LongTaskInfo.h"

LongTaskInfo::LongTaskInfo(const QString &content, const QDate &s):
    start(s), BaseInfo(Model::long_task, content)
{
}

LongTaskInfo::LongTaskInfo(const QJsonObject &obj):
    BaseInfo(Model::long_task)
{
    FromJson(obj);
}


void LongTaskInfo::FromJson(const QJsonObject &obj) {
    this->content = obj["content"].toString();
    this->start = QDate::fromString(obj["time-start"].toString());
    if (obj["is_complete"].toBool())
        this->Completed();
}

bool LongTaskInfo::IsShowByDate(const QDateTime &dt) const
{
    return dt.date() >= start;
}
QJsonObject LongTaskInfo::ToJson() const {
    return QJsonObject{
                       {"content", Content()},
                       {"type", Model::TypeToStr.value(Model::TypeToChinese.key(Type()))},
                       {"time-start", start.toString()},
                       {"is_complete", this->IsCompleted()}};
}
QString LongTaskInfo::Time() const
{
    int days = QDate::currentDate().daysTo(start);
    return QString("%1开始 | ").arg(start.toString("yyyy-MM-dd")) +
           ((days > 0) ? QString("%1日后").arg(days) : QString("开始%1").arg(-days));
}
