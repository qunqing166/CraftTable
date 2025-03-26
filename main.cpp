#include "MainWindow.h"

#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <QTextStream>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    static QSharedMemory* singleApp = new QSharedMemory("CraftTable");
    if(!singleApp->create(1))
    {
        a.quit();
        return -1;
    }

    QFile file(":/res/style/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&file);
        QString styleSheet = in.readAll();
        qApp->setStyleSheet(styleSheet);
    }

    MainWindow w;
    // w.show();
    return a.exec();
}
