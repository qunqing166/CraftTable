#include "TaskBuilder.h"

#include "CountdownDayInfo.h"
#include "DailyTask.h"
#include "LongTaskInfo.h"
#include "ScheduleInfo.h"
#include "TaskInfo.h"

BaseInfo *TaskBuilder::Create(const QJsonObject &obj)
{
    BaseInfo *info;
    Model::ModelType mType = Model::TypeToStr.key(obj["type"].toString());

    switch(mType)
    {
    case Model::countdown_day:
        return new CountdownDayInfo(obj);
    case Model::task:
        return new TaskInfo(obj);
    case Model::schedule:
        return new ScheduleInfo(obj);
    case Model::long_task:
        return new LongTaskInfo(obj);
    case Model::daily_task:
        return new DailyTask(obj);
    default:
        return nullptr;
    }
}

BaseInfo *TaskBuilder::Create(Model::ModelType type, const QString &content, const QDateTime &t1, const QDateTime &t2)
{
    switch (type) {
    case Model::countdown_day:
        return new CountdownDayInfo(content, t1.date());
    case Model::schedule:
        return new ScheduleInfo(content, t1, t2);;
    case Model::task:
        return new TaskInfo(content, t1);
    case Model::long_task:
        return new LongTaskInfo(content, t1.date());
    case Model::daily_task:
        return new DailyTask(content, t1.date(), t2.date());
    default:
        return nullptr;
    }
}
