#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    askForDirectoryPath();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete control;
}

void MainWindow::askForDirectoryPath()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    this->control = new ImageFinderControl(this, dir);
}

void MainWindow::setPath(QString path)
{
    ui->labelPath->setText(path);
}
