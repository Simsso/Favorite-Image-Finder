#ifndef IMAGEFINDERCONTROL_H
#define IMAGEFINDERCONTROL_H

#include <QString>
#include <QFileInfoList>

class MainWindow;

class ImageFinderControl
{
public:
    ImageFinderControl(MainWindow* ui, QString path);
    ~ImageFinderControl();

private:
    MainWindow* ui;
    QString directoryPath;
    QFileInfoList files;

    void loadFileNames();
};

#endif // IMAGEFINDERCONTROL_H
