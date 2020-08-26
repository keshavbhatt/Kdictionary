#-------------------------------------------------
#
# Project created by QtCreator 2017-12-27T18:40:35
#
#-------------------------------------------------

QT       += core gui sql webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kdictionary
TEMPLATE = app
CONFIG += c++11

# Set program version
VERSION = 0.2
DEFINES += VERSIONSTR=\\\"$${VERSION}\\\"

include(qhotkey.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
        cookiejar.cpp

HEADERS  += mainwindow.h \
            cookiejar.h

FORMS    += mainwindow.ui \
            menu.ui \
            instant_result.ui

RESOURCES += \
    res.qrc \
    style.qrc \
    browser.qrc \
    YoutubeDL.qrc


# Default rules for deployment.
isEmpty(PREFIX){
 PREFIX = /usr
}

BINDIR  = $$PREFIX/bin
DATADIR = $$PREFIX/share

target.path = $$BINDIR

icon.files = icons/kdictionary.png
icon.path = $$DATADIR/icons/hicolor/512x512/apps/

desktop.files = kdictionary.desktop
desktop.path = $$DATADIR/applications/

INSTALLS += target icon desktop
