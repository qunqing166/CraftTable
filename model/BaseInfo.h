#ifndef BASEINFO_H
#define BASEINFO_H

#include <QString>
#include <QJsonObject>
#include "ModelType.h"

class BaseInfo
{
public:
    BaseInfo(Model::ModelType type);
    virtual ~BaseInfo(){}

    virtual QString Content() const = 0;
    virtual QString Type() const;
    virtual QString Time() const = 0;
    virtual bool IsTimeout() const = 0;

    virtual QJsonObject ToJson() const;
    virtual void FromJson(const QJsonObject&) = 0;

    void Completed(){this->isCompleted = true;};
    bool IsCompleted() const {return isCompleted;}

private:
    Model::ModelType type;
    bool isCompleted = false;
};

#endif // BASEINFO_H
