#include "imagefindercontrol.h"
#include "mainwindow.h"

#include <vector>
#include <random>
#include <time.h>

#include <QDir>
#include <QDebug>

ImageFinderControl::ImageFinderControl(MainWindow* ui, QString path) : ui(ui), directoryPath(path)
{
    ui->setPath(path);
    this->init();

#ifdef QT_DEBUG
#else
    srand(time(NULL)); // true pseudo randomness
#endif
}

ImageFinderControl::~ImageFinderControl()
{
    //delete ui;
}

// searches the class' directory path for image files and stores them in the files attribute
void ImageFinderControl::loadFileNames()
{
    QDir directory(this->directoryPath);
    QStringList nameFilter;
    nameFilter << "*.png" << "*.jpg" << "*.jpeg" << "*.gif";
    this->files = directory.entryInfoList(nameFilter, QDir::Files);
    this->ui->showDirectoryInformation(this->files);
}

void ImageFinderControl::init()
{
    this->loadFileNames();

    int numFiles = this->files.size();
    if (numFiles > 0) { // files found
        if (numFiles == 1) {
            // only one file exists
            this->ui->showWinner(&this->files[0]);
        }
        else {
            // more than one file
            this->preferred = new bool[numFiles];
            for (int i = 0; i < numFiles; i++) {
                this->preferred[i] = true;
            }
            this->nextQuestion();
        }
    }
}

std::vector<const QFileInfo*> ImageFinderControl::getPreferredFiles() const
{
    std::vector<const QFileInfo*> preferredFiles;
    for (int i = 0; i < this->files.size(); i++) {
        if (this->preferred[i]) {
            preferredFiles.push_back(&this->files[i]);
        }
    }
    return preferredFiles;
}

bool ImageFinderControl::done()
{
    return this->getTwoRandomPreferredFiles().equal();
}

QFileInfoPair ImageFinderControl::getTwoRandomPreferredFiles() const
{
    QFileInfoPair fip;
    std::vector<const QFileInfo*> preferredFiles = this->getPreferredFiles();
    size_t index = (size_t)((rand() / (double)RAND_MAX) * preferredFiles.size());
    fip.a = preferredFiles[index++];
    fip.b = preferredFiles[(index < preferredFiles.size()) ? index : 0];
    return fip;
}

void ImageFinderControl::nextQuestion()
{
    if (this->done()) {
        this->ui->showWinner(this->getTwoRandomPreferredFiles().a);
    }
    else {
        this->currentImages = this->getTwoRandomPreferredFiles();
        this->ui->showImages(this->currentImages);
    }

    this->ui->setProgress(this->getProgress());
}

double ImageFinderControl::getProgress() const
{
    return 1 - ((double)this->getPreferredFiles().size() - 1) / this->files.size();
}

void ImageFinderControl::setChosenImage(bool aChosen)
{
    if (this->done()) {
        return;
    }

    const QFileInfo* notChosen = (!aChosen) ? this->currentImages.a : this->currentImages.b;
    int index = this->files.indexOf(*notChosen);
    this->preferred[index] = false;

    this->nextQuestion();
}
