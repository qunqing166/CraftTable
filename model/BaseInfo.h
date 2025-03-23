#ifndef BASEINFO_H
#define BASEINFO_H

#include <QString>
#include <QJsonObject>

class BaseInfo
{
public:
    BaseInfo() = default;

    virtual QString Content() const = 0;
    virtual QString Type() const = 0;
    virtual QString Time() const = 0;
    virtual bool IsTimeout() const = 0;

    virtual QJsonObject ToJson() const;
    virtual void FromJson(const QJsonObject&) = 0;
};

#endif // BASEINFO_H
