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
    mods/cbc.cpp \
    mods/cfb.cpp \
    mods/ctr.cpp \
    mods/ecb.cpp \
    mods/ofb.cpp \
    mods/magma.cpp \
    mods/macgenerator.cpp \
    elements/about.cpp \
    elements/encrypt.cpp \
    elements/keydialog.cpp

HEADERS  += mainwindow.h \
    mods/cbc.h \
    mods/cfb.h \
    mods/ctr.h \
    mods/ecb.h \
    mods/ofb.h \
    mods/magma.h \
    mods/macgenerator.h \
    elements/about.h \
    elements/keydialog.h \
    elements/encrypt.h

FORMS    += mainwindow.ui \
    elementsForms/about.ui \
    elementsForms/encrypt.ui \
    elementsForms/keyDialog.ui

RESOURCES += \
    res.qrc

win32:RC_ICONS += ./res/GOST_icon.ico
VERSION = 0.0.16.2
