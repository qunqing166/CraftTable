#include "DateTimeEditor.h"
#include "MonthDaySelector.h"
#include "NumSelector.h"

#include <QHBoxLayout>

DateTimeEditor::DateTimeEditor(QWidget *parent):
    QWidget(parent)
{
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
}
