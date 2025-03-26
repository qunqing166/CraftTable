#include "BaseInfo.h"

BaseInfo::BaseInfo(Model::ModelType type, const QString &content):
    type(type), content(content)
{

}

QString BaseInfo::Type() const
{
    return Model::TypeToChinese.value(this->type);
}

QJsonObject BaseInfo::ToJson() const {
    return QJsonObject{{"content", Content()}, {"type", Type()}, {"time", Time()}, {"is_complete", isCompleted}};
};
