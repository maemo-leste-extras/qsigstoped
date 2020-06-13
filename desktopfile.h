#ifndef DESKTOPFILE_H
#define DESKTOPFILE_H

#include<QString>

class DesktopFile
{
public:

    QString name;
    QString command;
    QString execName;
    QString iconPath;

    bool stop = false;

public:
    DesktopFile(const QString& fileName);
    DesktopFile(){}
    bool open(const QString& fileName);
    bool operator==(const DesktopFile& in);

    static QList<DesktopFile> getDesktopFiles(const QList<QByteArray>& desktopFileDirs);
};

#endif // DESKTOPFILE_H
