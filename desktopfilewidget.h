#ifndef DESKTOPFILEWIDGET_H
#define DESKTOPFILEWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include "desktopfile.h"

namespace Ui {
class DesktopFileWidget;
}

class DesktopFileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DesktopFileWidget(const DesktopFile& desktopfile, QWidget *parent = nullptr);
    ~DesktopFileWidget();

    bool isChecked();

protected:

    virtual void mousePressEvent(QMouseEvent* event);

private:
    Ui::DesktopFileWidget *ui;
};

#endif // DESKTOPFILEWIDGET_H
