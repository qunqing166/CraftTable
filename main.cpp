#include "MainWindow.h"

#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
