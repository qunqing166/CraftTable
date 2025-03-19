#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <QObject>

class FileManagement : public QObject
{
    Q_OBJECT

    QString savedFilePath;
    QString fileName;

public:
    explicit FileManagement(QObject *parent = nullptr);

    QString GetSavedFilePath() {return savedFilePath;}
    static FileManagement* Instance()
    {
        static FileManagement instance;
        return &instance;
    }

    QJsonObject LoadJsonFile();
    bool SaveJsonFile(const QJsonObject& obj);

private:
    bool IsFilePathExist();


signals:
};

#endif // FILEMANAGEMENT_H
