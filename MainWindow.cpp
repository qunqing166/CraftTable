#include "MainWindow.h"
#include "TaskEditWidget.h"
#include <QMenu>
#include <QEvent>
#include <QFile>

MainWindow::MainWindow(QObject *parent)
    : QObject(parent)
{
    // this->setFixedSize(900, 600);
    // this->setFixedSize(250, 500);
    // this->resize(250, 500);
    this->LoadStyleSheet();

    trayView = new TrayView(nullptr);
    taskEditor = new TaskEditWidget(nullptr);
    taskEditor->resize(250, 500);

    connect(trayView->GetTaskView(), &TaskView::Edit, taskEditor, &TaskEditWidget::OnTaskEdit);
    connect(trayView, &TrayView::CreateTask, taskEditor, &TaskEditWidget::OnTaskCreate);
    connect(taskEditor, &TaskEditWidget::TaskCreated, trayView, &TrayView::AddTask);
}

MainWindow::~MainWindow()
{
    delete trayView;
    delete taskEditor;
    // trayView->deleteLater();
    // taskEditor->deleteLater();
}

void MainWindow::LoadStyleSheet()
{
    QFile file(":/res/style/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&file);
        QString styleSheet = in.readAll();
        // this->setStyleSheet(styleSheet);
    }
}

