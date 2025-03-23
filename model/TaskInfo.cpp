#include "TaskInfo.h"
#include "../TimeEditor.h"

TaskInfo::TaskInfo(const QJsonObject &obj):
    BaseInfo(Model::task)
{
    FromJson(obj);
}

TaskInfo::TaskInfo(const QString &info, const QDateTime &dt):
    content(info), time(dt), BaseInfo(Model::task)
{

}

QString TaskInfo::Content() const
{
    return this->content;
}

QString TaskInfo::Time() const
{
    return time.toString("yyyy-MM-dd hh:mm ") + TimeEditor::GetDayOfWeek(time.date().dayOfWeek());
}

QJsonObject TaskInfo::ToJson() const
{
    return QJsonObject{{"content", Content()},
                       {"type", Model::TypeToStr.value(Model::TypeToChinese.key(Type()))},
                       {"time", time.toString()}};
}

void TaskInfo::FromJson(const QJsonObject &obj)
{
    this->content = obj["content"].toString();
    this->time = QDateTime::fromString(obj["time"].toString());
}

bool TaskInfo::IsTimeout() const
{
    return time.date() < QDate::currentDate();
}
