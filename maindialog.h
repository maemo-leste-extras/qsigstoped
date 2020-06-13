#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QVector>
#include "desktopfilewidget.h"

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

    QVector<DesktopFileWidget*> widgets_;

public:
    explicit MainDialog(QWidget *parent = nullptr);
    ~MainDialog();

    void setDesktopFiles(const QList<DesktopFile>& desktopFiles);

    QVector<DesktopFileWidget*> getWidgets();

private:
    Ui::MainDialog *ui;
};

#endif // MAINDIALOG_H
