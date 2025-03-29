#include "Utility.h"

QString Utility::GetDayOfWeek(int day) {
    QString ret;
    switch (day % 7) {
    case 0:
        ret = "周日";
        break;
    case 1:
        ret = "周一";
        break;
    case 2:
        ret = "周二";
        break;
    case 3:
        ret = "周三";
        break;
    case 4:
        ret = "周四";
        break;
    case 5:
        ret = "周五";
        break;
    case 6:
        ret = "周六";
        break;
    }
    return ret;
}

QString Utility::FormatDateTime(const QDateTime &dt)
{
    qDebug() << dt;
    return dt.toString("yyyy年MM月dd日 hh:mm ") + Utility::GetDayOfWeek(dt.date().dayOfWeek());
}
