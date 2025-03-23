#include "TaskInfo.h"

const QString TaskInfo::type = "task";

// TaskInfo::TaskInfo()
// {

// }

TaskInfo::TaskInfo(const QJsonObject &obj)
{
    FromJson(obj);
}

TaskInfo::TaskInfo(const QString &info, const QDateTime &dt):
    content(info), time(dt)
{

}

QString TaskInfo::Content() const
{
    return this->content;
}

QString TaskInfo::Type() const
{
    // return "task";
    return TaskInfo::type;
}

QString TaskInfo::Time() const
{
    return this->time.toString();
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

// QJsonObject TaskInfo::ToJson()
// {
//     return QJsonObject{{"content", this->Content()}, {"type", }}
// }

// TaskInfo::TaskInfo(const QString &content, const QDateTime &time):
//     content(content), time(time)
// {

// }

// TaskInfo TaskInfo::FromJson(const QJsonObject &obj)
// {
//     TaskInfo info;
//     info.content = obj["info"].toString();
//     // QString typeStr = obj["type"].toString();
//     // if(typeStr == "task")info.type = TaskType::task;
//     info.type = typeToStr.key(obj["type"].toString());

//     info.time = QDateTime::fromString(obj["time"].toString());
//     return info;
// }

// QMap<TaskInfo::TaskType, QString> TaskInfo::typeToStr =
// {
//     {TaskInfo::TaskType::task, "任务"},
//     {TaskInfo::TaskType::countdown_day, "倒数日"},
//     {TaskInfo::TaskType::schedule, "日程"}
//     // {TaskInfo::TaskType::task, "task"},
//     // {TaskInfo::TaskType::countdown_day, "countdown_day"}
// };

// QJsonObject TaskInfo::ToJson() {
//     return QJsonObject{{"info", content}, {"type", this->GetType()}, {"time", time.toString()}};
// }
// QString TaskInfo::GetType()
// {
//     return typeToStr.value(this->type);
// }
