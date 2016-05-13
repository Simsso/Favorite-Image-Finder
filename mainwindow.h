#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfoList>

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

    void setPath(QString path);
    void showDirectoryInformation(QFileInfoList files);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    ImageFinderControl* control;

    void askForDirectoryPath();
};

#endif // MAINWINDOW_H
