#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "TaskEditWidget.h"
#include "TrayView.h"

class MainWindow : public QObject//QMainWindow
{
    Q_OBJECT

    TrayView *trayView;
    TaskEditWidget *taskEditor;

public:
    // MainWindow(QWidget *parent = nullptr);
    MainWindow(QObject *parent = nullptr);
    ~MainWindow();

protected:
    // bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void LoadStyleSheet();

signals:
    // void EditingCompleted();
};
#endif // MAINWINDOW_H
