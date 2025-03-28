#include "MonthDaySelector.h"

MonthDaySelector::MonthDaySelector(QWidget *parent):
    AbstractDataSelector(parent)
{

}

QString MonthDaySelector::CurrentData()
{
    return date.toString("MM月dd日");
}

QString MonthDaySelector::NextData()
{
    return date.addDays(1).toString("MM月dd日");
}

QString MonthDaySelector::LastData()
{
    return date.addDays(-1).toString("MM月dd日");
}

void MonthDaySelector::ChangeData(bool isNext)
{
    date = date.addDays(isNext ? 1 : -1);
}
