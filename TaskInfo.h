#ifndef TASKINFO_H
#define TASKINFO_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>

class TaskInfo
{

public:

    enum TaskType
    {
      task
    };

    TaskInfo();
    TaskInfo(const QString& info, const TaskType& type, const QDateTime& dt);

    void SetContent(const QString& info){this->content = info;}
    QString GetContent(){return content;}
    QString GetType(){return "task/" + time.toString();}

    QJsonObject ToJson();

    static TaskInfo FromJson(const QJsonObject &obj);


private:
    QString content;
    TaskType type = task;
    QDateTime time = QDateTime::currentDateTime();
};

#endif // TASKINFO_H
