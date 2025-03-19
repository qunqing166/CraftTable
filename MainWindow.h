#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "TaskEditWidget.h"
#include "TrayView.h"

class MainWindow : public QObject
{
    Q_OBJECT

    TrayView *trayView;
    TaskEditWidget *taskEditor;

public:
    MainWindow(QObject *parent = nullptr);
    ~MainWindow();

};
#endif // MAINWINDOW_H
