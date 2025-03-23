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

    // enum TaskType
    // {
    //     task,
    //     countdown_day,
    //     schedule
    // };

    // TaskInfo();
    TaskInfo(const QJsonObject&);
    TaskInfo(const QString&, const QDateTime&);

    virtual QString Content() const override;
    virtual QString Type() const override;
    virtual QString Time() const override;

    // virtual QJsonObject ToJson() override;
    virtual void FromJson(const QJsonObject&) override;

    virtual bool IsTimeout() const override;

    // void SetContent(const QString& info){this->content = info;}
    // QString GetContent(){return content;}
    // QString GetType();
    // QDateTime GetTime(){return time;}

    // QJsonObject ToJson();

    // static TaskInfo FromJson(const QJsonObject &obj);
    static const QString type;

private:
    QString content;
    // TaskType type = task;
    QDateTime time = QDateTime::currentDateTime();

    // static QMap<TaskType, QString> typeToStr;
};

#endif // TASKINFO_H
