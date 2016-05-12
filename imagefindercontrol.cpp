#include "imagefindercontrol.h"
#include "mainwindow.h"

ImageFinderControl::ImageFinderControl(MainWindow* ui, QString path) : ui(ui), directoryPath(path)
{
    ui->setPath(path);
}

ImageFinderControl::~ImageFinderControl()
{
    delete ui;
}

void ImageFinderControl::loadFileNames()
{

}
