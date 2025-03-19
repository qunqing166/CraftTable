#include "TaskInfo.h"

TaskInfo::TaskInfo() {}

TaskInfo TaskInfo::FromJson(const QJsonObject &obj)
{
    TaskInfo info;
    info.info = obj["info"].toString();
    info.type = obj["type"].toString();
    info.time = QDateTime::fromString(obj["time"].toString());
    return info;
}

QJsonObject TaskInfo::ToJson() {
    return QJsonObject{{"info", info}, {"type", type}, {"time", time.toString()}};
}
