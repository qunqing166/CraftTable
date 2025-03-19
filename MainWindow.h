#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "TrayView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    TrayView *trayView;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void LoadStyleSheet();
};
#endif // MAINWINDOW_H
