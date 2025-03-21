#include "TaskInfo.h"

TaskInfo::TaskInfo()
{

}

TaskInfo::TaskInfo(const QString &info, const TaskType &type, const QDateTime &dt):
    content(info), type(type), time(dt)
{

}

TaskInfo TaskInfo::FromJson(const QJsonObject &obj)
{
    TaskInfo info;
    info.content = obj["info"].toString();
    // QString typeStr = obj["type"].toString();
    // if(typeStr == "task")info.type = TaskType::task;
    info.type = typeToStr.key(obj["type"].toString());

    info.time = QDateTime::fromString(obj["time"].toString());
    return info;
}

QMap<TaskInfo::TaskType, QString> TaskInfo::typeToStr =
{
    {TaskInfo::TaskType::task, "task"},
    {TaskInfo::TaskType::countdown_day, "countdown_day"}
};

QJsonObject TaskInfo::ToJson() {
    return QJsonObject{{"info", content}, {"task", this->GetType()}, {"time", time.toString()}};
}
QString TaskInfo::GetType()
{
    return typeToStr.value(this->type);
}
