#include "maindialog.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QString>
#include <QVector>
#include <QMessageBox>
#include <QDebug>
#include <sys/types.h>
#include <signal.h>
#include <QOpenGLContext>

#include "desktopfile.h"

void generateBlacklistFile(QString fileName, QVector<DesktopFileWidget*> widgets, const QList<DesktopFile>& desktopFiles, pid_t sigstopedPid)
{
    QFile blacklist(fileName);
    blacklist.open(QIODevice::WriteOnly | QIODevice::Truncate);
    if(!blacklist.isOpen())
    {
        QMessageBox::critical(nullptr, "Error", "Can not open: " + fileName );
    }
    else
    {
        for(int i = 0; i < widgets.size() && i < desktopFiles.size(); ++i)
        {
            if(widgets[i]->isChecked())
            {
                blacklist.write(desktopFiles[i].execName.toUtf8()+'\n');
                qDebug()<<desktopFiles[i].execName;
            }
        }
        kill(sigstopedPid, SIGUSR1);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug()<<(QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGLES ? "Using OpenGL|ES" : "Using OpenGL");
    pid_t sigstopedPid;
    QString pidfileName(QDir::home().path() + "/.config/sigstoped/pidfile");
    QFile pidfile(pidfileName);
    pidfile.open(QIODevice::ReadOnly);
    if(!pidfile.isOpen())
    {
        qDebug()<<QDir::home().path() + "/.config/sigstoped/pidfile";
        QMessageBox::critical(nullptr, "Error", "The sigstoped deamon must be running" );
        return 1;
    }
    else
    {
        sigstopedPid = pidfile.readAll().toLong();
        qDebug()<<"sigstoped pid:"<<sigstopedPid;
        pidfile.close();
    }

    QList<QByteArray> desktopFileDirs = qgetenv("XDG_DATA_DIRS").split(':');
    qDebug()<<"Looking for .desktop files in:";
    for(int i = 0; i < desktopFileDirs.size(); ++i) qDebug()<<QString(desktopFileDirs[i]);
    if(desktopFileDirs.size() == 0) QMessageBox::critical(nullptr, "Error", "XDG_DATA_DIRS must be set" );

    QFile blacklist(QDir::home().path() + "/.config/sigstoped/blacklist");
    blacklist.open(QIODevice::ReadOnly);

    QList<DesktopFile> desktopFiles = DesktopFile::getDesktopFiles(desktopFileDirs);
    if(blacklist.isOpen())
    {
        QList<QByteArray> blacklistedApplicationNames = blacklist.readAll().split('\n');
        if(blacklistedApplicationNames.size() > 0 && blacklistedApplicationNames.back() == "") blacklistedApplicationNames.pop_back();
        for(int i = 0; i < blacklistedApplicationNames.size(); ++i)
        {
            qDebug()<<blacklistedApplicationNames[i];
            for(int j = 0; j < desktopFiles.size(); ++j)
            {
                if(desktopFiles[j].execName.toUtf8() == blacklistedApplicationNames[i])
                {
                    desktopFiles[j].stop = true;
                }
            }
        }
    }


    MainDialog w;
    QObject::connect(&w, &MainDialog::accepted, [&w, &desktopFiles, &sigstopedPid](){generateBlacklistFile(QDir::home().path() + "/.config/sigstoped/blacklist", w.getWidgets(), desktopFiles, sigstopedPid);});

    w.setDesktopFiles(desktopFiles);

    w.show();
    return a.exec();
}
