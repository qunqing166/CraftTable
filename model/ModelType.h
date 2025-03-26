#ifndef MODELTYPE_H
#define MODELTYPE_H

#include <QMap>

namespace Model {

enum ModelType
{
    none,
    task,
    long_task,
    schedule,
    countdown_day
};

const QMap<ModelType, QString> TypeToStr{
    {none, ""},
    {task, "task"},
    {long_task, "long_task"},
    {schedule, "schedule"},
    {countdown_day, "countdown_day"}
};
const QMap<ModelType, QString> TypeToChinese{
    {none, ""},
    {task, "任务"},
    {long_task, "长任务"},
    {schedule, "日程"},
    {countdown_day, "倒数日"}
};


}



#endif // MODELTYPE_H
