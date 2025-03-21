#ifndef TASKINFO_H
#define TASKINFO_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include <QMap>

class TaskInfo
{

public:

    enum TaskType
    {
        task,
        countdown_day
    };

    TaskInfo();
    TaskInfo(const QString&, const TaskType&, const QDateTime&);


    void SetContent(const QString& info){this->content = info;}
    QString GetContent(){return content;}
    QString GetType();
    QDateTime GetTime(){return time;}

    QJsonObject ToJson();

    static TaskInfo FromJson(const QJsonObject &obj);

private:
    QString content;
    TaskType type = task;
    QDateTime time = QDateTime::currentDateTime();

    static QMap<TaskType, QString> typeToStr;
};

#endif // TASKINFO_H
