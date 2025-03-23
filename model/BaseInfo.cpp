#include "BaseInfo.h"

QJsonObject BaseInfo::ToJson() const {
    return QJsonObject{{"content", Content()}, {"type", Type()}, {"time", Time()}};
};
