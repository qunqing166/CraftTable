#include "LongTaskInfo.h"

LongTaskInfo::LongTaskInfo(const QString &content, const QDate &s):
    start(s), BaseInfo(Model::long_task, content)
{
}

QJsonObject LongTaskInfo::ToJson() const {
    return QJsonObject{
                       {"content", Content()},
                       {"type", Model::TypeToStr.value(Model::TypeToChinese.key(Type()))},
                       {"time-start", start.toString()},
                       {"is_complete", this->IsCompleted()}};
}
void LongTaskInfo::FromJson(const QJsonObject &obj) {
    this->content = obj["content"].toString();
    this->start = QDate::fromString(obj["time-start"].toString());
    if (obj["is_complete"].toBool())
        this->Completed();
}
