#ifndef MONTHDAYSELECTOR_H
#define MONTHDAYSELECTOR_H

#include "AbstractDataSelector.h"

#include <QDate>

class MonthDaySelector : public AbstractDataSelector
{
public:
    MonthDaySelector(QWidget *parent = nullptr);

    // AbstractDataSelector interface
protected:
    QString CurrentData() override;
    QString NextData() override;
    QString LastData() override;
    void ChangeData(bool isNext) override;

private:

    QDate date = QDate::currentDate();

};

#endif // MONTHDAYSELECTOR_H
