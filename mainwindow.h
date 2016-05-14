#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfoList>
#include <QGraphicsView>

#include "qfileinfopair.h"

#include "imagefindercontrol.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setPath(const QString path);
    void showDirectoryInformation(const QFileInfoList files);

    void showImages(const QFileInfoPair fip);
    void showWinner(const QFileInfo* fi);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    ImageFinderControl* control;

    /* used for showImage method */
    QGraphicsScene *scene;
    QPixmap image;

    void askForDirectoryPath();
    void showImage(const QString path, QGraphicsView* view);
};

#endif // MAINWINDOW_H
