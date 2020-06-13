#include "maindialog.h"
#include "ui_maindialog.h"

#include <QPushButton>
#include <QScroller>
#include <QTouchDevice>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(ui->buttonBox->Apply), &QPushButton::clicked, this, &MainDialog::accepted);
    QScroller::grabGesture(ui->scrollArea, QScroller::TouchGesture);
    QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);


    ui->scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
}

MainDialog::~MainDialog()
{
    delete ui;
    for(int i = 0; i<widgets_.size(); ++i) delete widgets_[i];
}

void MainDialog::setDesktopFiles(const QList<DesktopFile>& desktopFiles)
{
    for(int i = 0; i<desktopFiles.size(); ++i) widgets_.push_back(new DesktopFileWidget(desktopFiles[i]));
    for(int i = 0; i<widgets_.size(); ++i) ui->scollItemLayout->insertWidget(-1, widgets_[i]);
}

QVector<DesktopFileWidget*> MainDialog::getWidgets()
{
    return widgets_;
}

