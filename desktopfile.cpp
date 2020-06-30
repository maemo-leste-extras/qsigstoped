#include "desktopfile.h"

#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QDebug>
#include <QDir>

DesktopFile::DesktopFile(const QString& fileName)
{
    open(fileName);
}

bool DesktopFile::operator==(const DesktopFile& in)
{
    return execName == in.execName;
}

bool DesktopFile::open(const QString& fileName)
{
    if(QFile::exists(fileName))
    {
        QSettings desktopFile(fileName, QSettings::IniFormat);
        desktopFile.beginGroup("Desktop Entry");
        name = desktopFile.value("Name").toString();
        command = desktopFile.value("Exec").toString();
        execName = QFileInfo(command).fileName().split(' ').at(0);
        execName.truncate(15);
        return true;
    }
    else
    {
        qDebug()<<fileName<<" dose not exist.";
        return false;
    }
}
QList<DesktopFile> DesktopFile::getDesktopFiles(const QList<QByteArray>& desktopFileDirs)
{

    QList<DesktopFile> desktopFiles;

    for(int i = 0; i < desktopFileDirs.size(); ++i)
    {
        QDir directory(desktopFileDirs[i] + "/applications");
        if(directory.exists())
        {
            QStringList desktopFileNames = directory.entryList(QStringList() << "*.desktop",QDir::Files);
            for(int j = 0; j < desktopFileNames.size(); ++j)
            {
                DesktopFile desktopFile(directory.path() + "/" + desktopFileNames[j]);
                bool found = desktopFile.execName == "";
                for(int k = 0; k < desktopFiles.size(); ++k)if( desktopFile == desktopFiles[k] )
                {
                    found = true;
                    break;
                }

                if(!found)desktopFiles.push_back(desktopFile);
            }
        }
    }
    return desktopFiles;
}
