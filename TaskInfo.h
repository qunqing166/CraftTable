#ifndef TASKINFO_H
#define TASKINFO_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>

class TaskInfo
{

    QString info;
    QString type = "task";
    QDateTime time = QDateTime::currentDateTime();

public:
    TaskInfo();
    void SetInfo(const QString& info){this->info = info;}

    QString GetInfo(){return info;}
    QString GetType(){return type + "/" + time.toString();}

    static TaskInfo FromJson(const QJsonObject &obj);

    QJsonObject ToJson();
};

#endif // TASKINFO_H
