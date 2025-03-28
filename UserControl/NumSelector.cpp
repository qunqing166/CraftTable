#include "NumSelector.h"

NumSelector::NumSelector(QWidget *parent):
    AbstractDataSelector(parent)
{
    this->UpdateText();
}

NumSelector::NumSelector(int num, QWidget *parent, int min, int max):
    AbstractDataSelector(parent), num(num), min(min), max(max)
{
    this->UpdateText();
}

void NumSelector::SetRange(int min, int max)
{
    this->min = min;
    this->max = max;
}

QString NumSelector::CurrentData()
{
    return QString::number(num);
}

QString NumSelector::NextData()
{
    if(num + 1 > max)return QString();
    return QString::number(num + 1);
}

QString NumSelector::LastData()
{
    if(num - 1 < min)return QString();
    return QString::number(num - 1);
}

void NumSelector::ChangeData(bool isNext)
{
    if (isNext)
    {
        if(num + 1 <= max)num++;
    }
    else
    {
        if(num - 1 >= min)num--;
    }
    qDebug() << num;
}
