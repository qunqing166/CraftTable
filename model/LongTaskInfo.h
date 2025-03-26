#ifndef LONGTASKINFO_H
#define LONGTASKINFO_H

#include "BaseInfo.h"
#include <QDate>

class LongTaskInfo: public BaseInfo
{
public:
    LongTaskInfo(const QString& con, const QDate& s);
    LongTaskInfo(const QJsonObject& obj);

    QString Content() const override{return content;}
    QString Time() const override;

    // 没有截止时间, 由用户完成之后手动标志完成
    bool IsTimeout() const override{ return false; }
    QJsonObject ToJson() const override;
    void FromJson(const QJsonObject &obj) override;
    bool IsShowByDate(const QDateTime &dt) const override;

private:
    QDate start;


};

#endif // LONGTASKINFO_H
