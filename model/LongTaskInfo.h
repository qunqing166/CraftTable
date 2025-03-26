#ifndef LONGTASKINFO_H
#define LONGTASKINFO_H

#include "BaseInfo.h"
#include <QDate>
class LongTaskInfo: public BaseInfo
{
public:
    LongTaskInfo(const QString& con, const QDate& s);

    QString Content() const{return content;}
    QString Time() const{return start.toString();}

    // 没有截止时间, 由用户完成之后手动标志完成
    bool IsTimeout() const { return false; }
    QJsonObject ToJson() const;
    void FromJson(const QJsonObject &obj);

private:
    // QString content;
    QDate start;
};

#endif // LONGTASKINFO_H
