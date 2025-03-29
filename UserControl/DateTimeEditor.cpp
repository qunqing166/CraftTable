#include "DateTimeEditor.h"
#include "MonthDaySelector.h"
#include "NumSelector.h"

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

    MonthDaySelector *mdsele = new MonthDaySelector(this);
    NumSelector* numSele1 = new NumSelector(0, this, 0, 24);
    numSele1->SetSuffix("时");
    NumSelector* numSele2 = new NumSelector(0, this, 0, 24);
    numSele2->SetSuffix("分");
    hLayout->addWidget(mdsele);
    hLayout->addWidget(numSele1);
    hLayout->addWidget(numSele2);

    this->setStyleSheet("background-color:white;");
}
