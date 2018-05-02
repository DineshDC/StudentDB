#-------------------------------------------------
#
# Project created by QtCreator 2018-04-27T11:24:25
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StudentDB
TEMPLATE = app
QTPLUGIN += QSQLMYSQL
CONFIG += c++1z
DEPENDPATH += . framelesswindow darkstyle_src
INCLUDEPATH += . framelesswindow darkstyle_src

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    framelesswindow/framelesswindow.cpp \
    framelesswindow/windowdragger.cpp \
    darkstyle_src/DarkStyle.cpp \
    course.cpp \
    iperson.cpp \
    student.cpp \
    professor.cpp \
    db_tables.cpp \
    datatable.cpp \
    customtable.cpp

HEADERS += \
        mainwindow.h \
    framelesswindow/framelesswindow.h \
    framelesswindow/windowdragger.h \
    darkstyle_src/DarkStyle.h \
    course.h \
    iperson.h \
    student.h \
    professor.h \
    db_tables.h \
    datatable.h \
    customtable.h

FORMS += \
        mainwindow.ui \
    framelesswindow/framelesswindow.ui \
    course.ui

RESOURCES += \
    darkstyle.qrc \
    framelesswindow.qrc
