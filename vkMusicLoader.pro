#-------------------------------------------------
#
# Project created by QtCreator 2016-05-08T13:54:00
#
#-------------------------------------------------

QT       += core gui
QT += webkitwidgets
QT += network
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vkcom
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    config.cpp \
    request.cpp \
    authorization.cpp \
    audio.cpp \
    utils.cpp \
    downloader.cpp \
    downloadmanager.cpp \
    downloaderui.cpp

HEADERS  += widget.h \
    config.h \
    request.h \
    authorization.h \
    audio.h \
    utils.h \
    downloader.h \
    downloadmanager.h \
    downloaderui.h

FORMS    += widget.ui \
    mainview.ui

RESOURCES += \
    resources.qrc
