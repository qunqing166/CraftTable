#ifndef TASKINFO_H
#define TASKINFO_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include <QMap>
#include "BaseInfo.h"

class TaskInfo: public BaseInfo
{

public:
    TaskInfo(const QJsonObject&);
    TaskInfo(const QString&, const QDateTime&);
    ~TaskInfo(){}

    virtual QString Content() const override;
    virtual QString Time() const override;

    virtual QJsonObject ToJson() const override;
    virtual void FromJson(const QJsonObject&) override;

    virtual bool IsTimeout() const override;

    QDateTime GetTime() const {return time;}

private:
    // QString content;
    QDateTime time = QDateTime::currentDateTime();

};

#endif // TASKINFO_H
