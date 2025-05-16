#ifndef TASKBUILDER_H
#define TASKBUILDER_H

#include "BaseInfo.h"
#include <QJsonObject>

class TaskBuilder
{
public:
    static BaseInfo* Create(const QJsonObject& obj);
    static BaseInfo* Create(Model::ModelType type, const QString& content, const QDateTime& t1, const QDateTime& t2);
};

#endif // TASKBUILDER_H
