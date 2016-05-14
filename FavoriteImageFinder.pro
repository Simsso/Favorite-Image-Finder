#-------------------------------------------------
#
# Project created by QtCreator 2016-05-10T21:50:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FavoriteImageFinder
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imagefindercontrol.cpp

HEADERS  += mainwindow.h \
    imagefindercontrol.h \
    qfileinfopair.h

FORMS    += mainwindow.ui
