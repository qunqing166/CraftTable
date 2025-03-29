#ifndef DATETIMEEDITOR_H
#define DATETIMEEDITOR_H

#include "MonthDaySelector.h"
#include "NumSelector.h"

#include <QWidget>
#include <QLabel>
#include <QDateTime>

class DateTimeEditor : public QWidget
{
    Q_OBJECT

public:
    DateTimeEditor(QWidget *parent = nullptr);

    void SetDateTime(const QDateTime& dt);

private:

    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    MonthDaySelector *mdsele;
    NumSelector* numSele1;
    NumSelector* numSele2;

signals:
    void ValueChanged(const QDateTime& dt);

};

#endif // DATETIMEEDITOR_H
