#include "imagefindercontrol.h"
#include "mainwindow.h"

#include <QDir>

ImageFinderControl::ImageFinderControl(MainWindow* ui, QString path) : ui(ui), directoryPath(path)
{
    ui->setPath(path);
    this->loadFileNames();
}

ImageFinderControl::~ImageFinderControl()
{
    //delete ui;
}

void ImageFinderControl::loadFileNames()
{
    QDir directory(this->directoryPath);
    QStringList nameFilter;
    nameFilter << "*.png" << "*.jpg" << "*.gif";
    this->files = directory.entryInfoList(nameFilter, QDir::Files);
    this->ui->showDirectoryInformation(this->files);
}
