#-------------------------------------------------
#
# Project created by QtCreator 2013-11-04T21:13:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Proton
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    view.cpp \
    items.cpp \
    game.cpp \
    utils.cpp

HEADERS  += window.h \
    view.h \
    items.h \
    game.h \
    utils.h

FORMS    += window.ui

RESOURCES += \
    proton.qrc
