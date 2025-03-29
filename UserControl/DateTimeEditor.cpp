#include "DateTimeEditor.h"
#include "MonthDaySelector.h"
#include "NumSelector.h"
// #include "../utility/Utility.h"
#include <QHBoxLayout>

DateTimeEditor::DateTimeEditor(QWidget *parent):
    QWidget(parent)
{
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    // this->setAttribute(Qt::WA_StyledBackground);
    // this->setAttribute(Qt::WA_TranslucentBackground);
    // this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    this->resize(200, 200);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    this->setLayout(hLayout);

    mdsele = new MonthDaySelector(this);
    numSele1 = new NumSelector(0, this, 0, 24);
    numSele1->SetSuffix("时");
    numSele2 = new NumSelector(0, this, 0, 24);
    numSele2->SetSuffix("分");
    hLayout->addWidget(mdsele);
    hLayout->addWidget(numSele1);
    hLayout->addWidget(numSele2);

    this->setStyleSheet("background-color:white;");

    connect(mdsele, &MonthDaySelector::ValueChanged, this, [&](const QDate& date){
        this->date = date;
        emit ValueChanged(QDateTime(date, time));
    });
    connect(numSele1, &NumSelector::ValueChanged, this, [&](int h){
        this->time.setHMS(h, this->time.minute(), 0);
        emit ValueChanged(QDateTime(date, time));
    });
    connect(numSele2, &NumSelector::ValueChanged, this, [&](int m){
        this->time.setHMS(this->time.hour(), m, 0);
        emit ValueChanged(QDateTime(date, time));
    });
}

void DateTimeEditor::SetDateTime(const QDateTime &dt)
{
        date = dt.date();
        time = dt.time();
        mdsele->SetValue(date);
        numSele1->SetValue(time.hour());
        numSele2->SetValue(time.minute());
}
// void DateTimeEditor::SetEditedDateTime(QDateTime *dt)
// {
//     editedDt = dt;
//     date = dt->date();
//     time = dt->time();
//     mdsele->SetValue(date);
//     numSele1->SetValue(time.hour());
//     numSele2->SetValue(time.minute());
//     connect(this, &DateTimeEditor::ValueChanged, this, [&](){
//         editedDt->setDate(date);
//         editedDt->setTime(time);
//     });
// }
// void DateTimeEditor::SetEditedLabel(QLabel *label)
// {
//     editedLabel = label;
//     connect(this, &DateTimeEditor::ValueChanged, this, [&](){
//         editedLabel->setText(Utility::FormatDateTime(QDateTime(date, time)));
//     });
// }
