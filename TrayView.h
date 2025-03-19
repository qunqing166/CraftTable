#ifndef TRAYVIEW_H
#define TRAYVIEW_H

#include <QSystemTrayIcon>
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QStackedLayout>

class TrayView: public QWidget
{
    Q_OBJECT

    QSystemTrayIcon *trayIcon;
    QTimer *hoverCheckTimer;
    QLabel *label1;
    QLabel *label2;
    QStackedLayout *sLayout;

public:
    TrayView(QWidget *parent = nullptr);

private:
    void ObjectInit();
    void WidgetInit();

    void CheckTrayIconMouseHover();

protected:
    void paintEvent(QPaintEvent*) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

};

#endif // TRAYVIEW_H
