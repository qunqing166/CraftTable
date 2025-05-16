#ifndef MODELTYPE_H
#define MODELTYPE_H

#include <QMap>
#include <QColor>

namespace Model {

/**
 * 添加一个新的任务类型:
 * 1.在@ModelType.h中注册新的类型及其中英文名称
 * 2.在/Model文件夹下创建新的类并继承@BaseInfo, 根据注释实现方法
 * * 到这里已经可以在创建任务界面看到新的类型了
 * 3.在下列方法中添加对应代码
 *      TaskEditDialog::ShowEditedItem      编辑界面
 *      TaskEditDialog::SetTaskInfo         将对象数据传入编辑器
 * 4.
 */

/**
 * @brief The ModelType enum    所有的任务类型
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

/**
 * @brief TypeToStr     任务类型与英文名的映射
 */
const QMap<ModelType, QString> TypeToStr{
    {none, ""},
    {task, "task"},
    {long_task, "long_task"},
    {schedule, "schedule"},
    {countdown_day, "countdown_day"},
    {daily_task, "daily_task"}
};

/**
 * @brief TypeToChinese     任务类型与中文名的映射
 */
const QMap<ModelType, QString> TypeToChinese{
    {none, ""},
    {task, "任务"},
    {long_task, "长任务"},
    {schedule, "日程"},
    {countdown_day, "倒数日"},
    {daily_task, "每日任务"}
};

/**
 * @brief QPair::second, QPair::first
 */
const QMap<ModelType, QPair<QColor, QColor>> TypeToColor{
    {none, {"#ffffffff", "#ffffffff"}},
    {task, {"#7ea3cf", "#b8d7fc"}},
    {long_task, {"#98da7a", "#cfffb9"}},
    {schedule, {"#8382f9", "#c7c7ff"}},
    {countdown_day, {"#c7706a", "#ffa49e"}},
    {daily_task, {"#8382f9", "#c7c7ff"}}
};



}



#endif // MODELTYPE_H
