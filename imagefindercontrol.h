#ifndef IMAGEFINDERCONTROL_H
#define IMAGEFINDERCONTROL_H

#include <vector>

#include <QString>
#include <QFileInfoList>

#include "qfileinfopair.h"

class MainWindow;

class ImageFinderControl
{
public:
    ImageFinderControl(MainWindow *ui, const QString path);
    ~ImageFinderControl();

    void setChosenImage(bool aChosen);

private:
    MainWindow *ui;
    QString directoryPath;
    QFileInfoList files;

    QFileInfoPair currentImages;

    bool *preferred;

    void loadFileNames();
    void init();
    void nextQuestion();
    bool done();

    double getProgress() const;

    QFileInfoPair getTwoRandomPreferredFiles() const;
    std::vector<const QFileInfo*> getPreferredFiles() const;
};

#endif // IMAGEFINDERCONTROL_H
