#ifndef BASEINFO_H
#define BASEINFO_H

#include <QString>
#include <QJsonObject>
#include "ModelType.h"

class BaseInfo
{
public:
    BaseInfo(Model::ModelType type, const QString& content = QString());
    virtual ~BaseInfo(){}

    /**
     * @brief Content 获取具体内容, 通常使用默认的, 如有需要可以重载
     * @return 内容
     */
    virtual QString Content() const {return content;}

    /**
     * @brief Type  获取任务类型, 该类型需要再头文件ModelType中注册, 初始化时需要传入任务类型
     *              通常使用默认的操作
     * @return 类型名称的中文字符串
     */
    virtual QString Type() const;

    /**
     * @brief Time 获取用于显示的格式化后的字符串
     * @return 格式化后的时间字符串
     */
    virtual QString Time() const = 0;

    /**
     * @brief IsTimeout 判断该任务是否已经超时
     * @return 是否超时
     */
    virtual bool IsTimeout() const = 0;

    /**
     * @brief IsShowByDate 根据日期判断是否显示
     * @param dt 需要用来判断的日期
     * @return 是否显示
     */
    virtual bool IsShowByDate(const QDateTime& dt) const = 0;

    /**
     * @brief ToJson    将所有信息格式化为json
     *                  通常使用默认操作, 如果出现多个时间字段, 建议重载
     * @return 格式化后的json对象
     */
    virtual QJsonObject ToJson() const;

    /**
     * @brief FromJson  从json对象中获取信息, 与ToJson相反的操作
     */
    virtual void FromJson(const QJsonObject&) = 0;

    void Completed(){this->isCompleted = true;};
    bool IsCompleted() const {return isCompleted;}

protected:
    QString content;

private:

    Model::ModelType type;
    bool isCompleted = false;
};

#endif // BASEINFO_H
