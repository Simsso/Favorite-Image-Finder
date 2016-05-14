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

void MainWindow::showImage(const QString path, QGraphicsView* view)
{
    this->image.load(path);
    this->scene = new QGraphicsScene(this);
    this->scene->addPixmap(image);
    this->scene->setSceneRect(image.rect());

    view->setScene(scene);
}

void MainWindow::showWinner(const QFileInfo *fi)
{

}

void MainWindow::on_pushButton_clicked()
{
    this->askForDirectoryPath();
}
