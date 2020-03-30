#-------------------------------------------------
#
# Project created by QtCreator 2013-03-30T21:19:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graphs
TEMPLATE = app


SOURCES += main.cpp\
        graphicFrame.cpp \
        mainwindow.cpp \
        point.cpp \
        position.cpp \
        utils.cpp

HEADERS  += mainwindow.h \
    graphicFrame.h \
    json.hpp \
    point.h \
    position.h \
    utils.h

FORMS    += mainwindow.ui

CONFIG += C++14
QMAKE_CXXFLAGS += -std=c++14
