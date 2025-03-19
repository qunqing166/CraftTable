#include "MainWindow.h"

#include <QApplication>
#include <QDir>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 获取文档目录路径
    QString docPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    qDebug() << "Documents Path:" << docPath;
    QString savedPath = docPath + "/Craft Table";
    // 检查路径是否存在
    if (!QDir(savedPath).exists()) {
        qDebug() << "Documents directory does not exist!";

        if(!QDir().mkdir(savedPath))
        {
            qDebug() << "目录创建失败";
            return -1;
        }
    }

    MainWindow w;
    // w.show();
    return a.exec();
}
