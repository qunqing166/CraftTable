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
    // taskEditor = new TaskEditWidget(nullptr);
    // taskEditor->resize(250, 500);

    // connect(trayView->GetTaskView(), &TaskView::Edit, taskEditor, &TaskEditWidget::OnTaskEdit);
    // connect(trayView, &TrayView::CreateTask, taskEditor, &TaskEditWidget::OnTaskCreate);
    // connect(taskEditor, &TaskEditWidget::TaskCreated, trayView, &TrayView::AddTask);
}

MainWindow::~MainWindow()
{
    delete trayView;
    // delete taskEditor;
}

