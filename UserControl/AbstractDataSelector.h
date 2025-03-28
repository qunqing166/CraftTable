#pragma once

#include <QLabel>
#include <QPropertyAnimation>
#include <QWidget>

class AbstractDataSelector : public QWidget
{
    Q_OBJECT

public:

    AbstractDataSelector(QWidget *parent = nullptr);

    QString GetCurrentData();
    void SetCurrentData(const QString& data);

    void SetBackgroundColor(const QColor&);
    void SetTextColor(const QColor&);
    void SetLineColor(const QColor&);

protected:

    virtual QString CurrentData(){return QString();};
    virtual QString NextData(){return QString();};
    virtual QString LastData(){return QString();};
    virtual void ChangeData(bool isNext){};
    virtual bool IsNextable(){return true;}
    virtual bool IsLastable(){return true;}

    void paintEvent(QPaintEvent * event) override;
    void wheelEvent(QWheelEvent *event) override;

    void UpdateText();

private:



    Q_PROPERTY(int Dy READ Dy WRITE SetDy)

    void SetDy(int d){dy = d;}
    int Dy() const {return dy;}

    int dy = 0;
    bool isNext;
    bool isDyHalf = false;

    QPropertyAnimation *animaDy;
    QLabel *labelCrt;
    QLabel *labelNext;
    QLabel *labelLast;
    QFrame *line1;
    QFrame *line2;

};
