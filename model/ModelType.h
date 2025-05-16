#ifndef MODELTYPE_H
#define MODELTYPE_H

#include <QMap>

namespace Model {

/**
 * 添加一个新的任务类型:
 * 1.在@ModelType.h中注册新的类型及其中英文名称
 * 2.在/Model文件夹下创建新的类并继承@BaseInfo, 根据注释实现方法
 * * 到这里已经可以在创建任务界面看到新的类型了
 * 3.在下列方法中添加对应代码
 *      TaskEditDialog::ShowEditedItem      编辑界面
 *      TaskEditDialog::SetTaskInfo         将对象数据传入编辑器
 *      TaskEditDialog::GetTaskInfo         将编辑器数据传入对象
 * 4.
 */

enum ModelType
{
    none,
    task,
    long_task,
    schedule,
    countdown_day,
    daily_task
};

const QMap<ModelType, QString> TypeToStr{
    {none, ""},
    {task, "task"},
    {long_task, "long_task"},
    {schedule, "schedule"},
    {countdown_day, "countdown_day"},
    {daily_task, "daily_task"}
};
const QMap<ModelType, QString> TypeToChinese{
    {none, ""},
    {task, "任务"},
    {long_task, "长任务"},
    {schedule, "日程"},
    {countdown_day, "倒数日"},
    {daily_task, "每日任务"}
};


}



#endif // MODELTYPE_H
