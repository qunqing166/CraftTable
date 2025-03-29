#ifndef NUMSELECTOR_H
#define NUMSELECTOR_H

#include "AbstractDataSelector.h"

class NumSelector:public AbstractDataSelector
{
    Q_OBJECT

public:
    NumSelector(QWidget *parent = nullptr);
    NumSelector(int num, QWidget *parent = nullptr, int min = -100, int max = 100);

    void SetValue(int value);
    void SetRange(int min, int max);
    void SetSuffix(const QString &s);

protected:
    QString CurrentData() override;
    QString NextData() override;
    QString LastData() override;
    void ChangeData(bool isNext) override;
    bool IsNextable() override{return num + 1 <= max;}
    bool IsLastable() override{return num - 1 >= min;}

private:
    int num = 0;
    int min = -100;
    int max = 100;
    QString suffix = "";

signals:

    void ValueChanged(int);
};

#endif // NUMSELECTOR_H
