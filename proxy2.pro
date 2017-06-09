#-------------------------------------------------
#
# Project created by QtCreator 2017-06-07T00:00:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proxy2
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -pthread
LIBS += -pthread

SOURCES += main.cpp\
        mainwindow.cpp \
    includes.cpp \
    reader.cpp \
    writer.cpp

HEADERS  += mainwindow.h \
    includes.h \
    reader.h \
    writer.h

FORMS    += mainwindow.ui
