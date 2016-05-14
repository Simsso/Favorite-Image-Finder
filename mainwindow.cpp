#include <QFileDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDesktopServices>

#include <algorithm>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //askForDirectoryPath();
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

void MainWindow::showDirectoryInformation(QFileInfoList files)
{
    ui->listWidgetFiles->clear();
    for (int i = 0; i < files.size(); i++) {
        ui->listWidgetFiles->addItem(files[i].fileName());
    }
}

void MainWindow::showImages(const QFileInfoPair fip)
{
    this->showImage(fip.a->absoluteFilePath(), this->ui->graphicsViewA);
    this->showImage(fip.b->absoluteFilePath(), this->ui->graphicsViewB);
}

void MainWindow::showImage(const QString path, QGraphicsView* view, bool autoScale)
{
    this->image.load(path);

    this->scene = new QGraphicsScene(this);
    this->scene->setSceneRect(0, 0, image.width(), image.height());
    this->scene->addPixmap(image);

    double scale = 1.0;
    if (autoScale) {
        int xView = view->width(), yView = view->height();
        int xImg = this->image.width(), yImg = this->image.height();
        double tmpScale = std::min(xView / (double)xImg, yView / (double)yImg);

        if (tmpScale < 1) { // don't zoom in (only out)
            scale = tmpScale;
        }
    }

    view->matrix().reset();
    view->resetMatrix();
    view->scale(scale, scale);

    view->setScene(scene);
}

void MainWindow::showWinner(const QFileInfo *fi)
{
    this->showImage(fi->absoluteFilePath(), this->ui->graphicsViewA);
    this->showImage(fi->absoluteFilePath(), this->ui->graphicsViewB);

    QString path = fi->absoluteFilePath();

    // open file in default program
#ifdef Q_WS_WIN
    if (QFileInfo(path).isDir())
        QProcess::startDetached("explorer", QStringList(path));
    else
#endif
        QDesktopServices::openUrl(QUrl(path));
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    switch(e->key()) {
    case 65:
        this->control->setChosenImage(true);
        break;
    case 66:
        this->control->setChosenImage(false);
        break;
    }
}

void MainWindow::setProgress(double x)
{
    this->ui->mainProgress->setValue(x * 1000);
}

void MainWindow::on_pushButton_clicked()
{
    this->askForDirectoryPath();
}

void MainWindow::on_btnImgA_clicked()
{
    // user prefers the left image (A)
    this->control->setChosenImage(true);
}

void MainWindow::on_btnImgB_clicked()
{
    // user prefers the right image (B)
    this->control->setChosenImage(false);
}
