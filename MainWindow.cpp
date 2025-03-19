#include "MainWindow.h"
#include <QMenu>
#include <QEvent>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(900, 600);

    trayView = new TrayView(this);
    this->LoadStyleSheet();
}

MainWindow::~MainWindow()
{
    trayView->deleteLater();
}

void MainWindow::LoadStyleSheet()
{
    QFile file(":/res/style/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&file);
        QString styleSheet = in.readAll();
        this->setStyleSheet(styleSheet);
    }
}

