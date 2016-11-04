#-------------------------------------------------
#
# Project created by QtCreator 2016-10-31T13:37:37
#
#-------------------------------------------------

QT       += core gui widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MisterGOSTec
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    magma.cpp \
    macgenerator.cpp \
    ecb.cpp \
    keydialog.cpp \
    encrypt.cpp \
    about.cpp \
    cbc.cpp \
    cfb.cpp \
    ofb.cpp \
    ctr.cpp

HEADERS  += mainwindow.h \
    macgenerator.h \
    magma.h \
    ecb.h \
    keydialog.h \
    encrypt.h \
    about.h \
    cbc.h \
    cfb.h \
    ofb.h \
    ctr.h

FORMS    += mainwindow.ui \
    keyDialog.ui \
    encrypt.ui \
    about.ui

RESOURCES += \
    res.qrc
