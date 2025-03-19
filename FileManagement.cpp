#include "FileManagement.h"
#include <QCryptographicHash>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>



FileManagement::FileManagement(QObject *parent)
    : QObject{parent}
{
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData("save");
    fileName = hash.result().toHex();
    qDebug() << "SHA-256 Hash:" << fileName;

    this->savedFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Craft Table";
    if (!QDir(savedFilePath).exists()) {
        qDebug() << "Documents directory does not exist!";
        if(!QDir().mkdir(savedFilePath))
        {
            qDebug() << "目录创建失败";
        }
    }
}

QJsonObject FileManagement::LoadJsonFile()
{
    QString filePath = savedFilePath + "/" + fileName;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "can not open the file!";
    }
    QJsonObject obj = QJsonDocument::fromJson(file.readAll()).object();
    file.close();

    return obj;
}

bool FileManagement::SaveJsonFile(const QJsonObject &obj)
{
    QString filePath = savedFilePath + "/" + fileName;
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "can not open the file!";
        return false;
    }

    file.write(QJsonDocument(obj).toJson());
    file.close();

    return true;
}

bool FileManagement::IsFilePathExist()
{
    return QDir(savedFilePath).exists();
}
