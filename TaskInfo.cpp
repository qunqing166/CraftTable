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

    QString typeStr = obj["type"].toString();
    if(typeStr == "task")info.type = TaskType::task;

    info.time = QDateTime::fromString(obj["time"].toString());
    return info;
}

QJsonObject TaskInfo::ToJson() {
    QJsonObject obj{{"info", content}, {"time", time.toString()}};
    QString typeStr;
    switch (type) {
    case task:
        typeStr = "task";
        break;
    default:
        break;
    }
    obj.insert("type", typeStr);
    return obj;
}
