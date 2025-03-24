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

    void SetStatus(bool is){this->isComplete = is;};
    bool Status(){return isComplete;};

private:
    Model::ModelType type;
    bool isComplete = false;
};

#endif // BASEINFO_H
