#ifndef DATETIMEEDITOR_H
#define DATETIMEEDITOR_H

#include <QWidget>
#include <QLabel>

class DateTimeEditor : public QWidget
{
    Q_OBJECT

public:
    DateTimeEditor(QWidget *parent = nullptr);

    void SetEditedLabel(QLabel* label){editedLabel = label;}
    void SetEditedDateTime(QDateTime* dt){editedDt = dt;}

private:

    QLabel* editedLabel = nullptr;
    QDateTime *editedDt = nullptr;

};

#endif // DATETIMEEDITOR_H
