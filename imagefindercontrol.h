#ifndef IMAGEFINDERCONTROL_H
#define IMAGEFINDERCONTROL_H

#include <vector>

#include <QString>

class MainWindow;

class ImageFinderControl
{
public:
    ImageFinderControl(MainWindow* ui, QString path);
    ~ImageFinderControl();
private:
    MainWindow* ui;
    QString directoryPath;
    std::vector<QString> fileNames;

    void loadFileNames();
};

#endif // IMAGEFINDERCONTROL_H
