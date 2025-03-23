#include "MainWindow.h"
#include "TaskEditDialog.h"
#include <QMenu>
#include <QEvent>
#include <QFile>

MainWindow::MainWindow(QObject *parent)
    : QObject(parent)
{
    // this->resize(250, 500);
    trayView = new TrayView(nullptr);
}

MainWindow::~MainWindow()
{
    delete trayView;
    // delete taskEditor;
}

