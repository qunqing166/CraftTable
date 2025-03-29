#ifndef MONTHDAYSELECTOR_H
#define MONTHDAYSELECTOR_H

#include "AbstractDataSelector.h"

#include <QDate>

class MonthDaySelector : public AbstractDataSelector
{
    Q_OBJECT

public:
    MonthDaySelector(QWidget *parent = nullptr);

    void SetValue(const QDate& time);

    // AbstractDataSelector interface
protected:
    QString CurrentData() override;
    QString NextData() override;
    QString LastData() override;
    void ChangeData(bool isNext) override;

private:

    QDate date = QDate::currentDate();

signals:
    void ValueChanged(const QDate&);

};

#endif // MONTHDAYSELECTOR_H
