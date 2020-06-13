#include "desktopfilewidget.h"
#include "ui_desktopfilewidget.h"
#include <QDebug>

DesktopFileWidget::DesktopFileWidget(const DesktopFile& desktopfile, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DesktopFileWidget)
{
    ui->setupUi(this);
    ui->label->setText(desktopfile.name);
    ui->checkBox->setChecked(desktopfile.stop);
    ui->checkBox->setStyleSheet("QCheckBox::indicator { width: 32px; height: 32px; } ");

    ui->checkBox->setTristate(false);

}

DesktopFileWidget::~DesktopFileWidget()
{
    delete ui;
}

bool DesktopFileWidget::isChecked()
{
    return ui->checkBox->isChecked();
}

void DesktopFileWidget::mousePressEvent(QMouseEvent *event)
{
    ui->checkBox->setCheckState(ui->checkBox->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked);
}
