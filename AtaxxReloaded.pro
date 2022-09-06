#-------------------------------------------------
#
# Project created by QtCreator 2019-05-03T15:24:35
#
#-------------------------------------------------

QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AtaxxReloaded
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += console

SOURCES += \
        src/main.cpp \
        src/graphic/mainwindow.cpp \
        src/graphic/options.cpp \
        src/graphic/graphicarray.cpp\
        src/graphic/game.cpp\
        src/graphic/menu.cpp\
        src/pion.cpp\
        src/console/console.cpp


HEADERS += \
        src/headers/mainwindow.h \
        src/headers/options.h \
        src/headers/graphicarray.h\
        src/headers/game.h\
        src/headers/menu.h\
        src/headers/pion.h\
        src/headers/console.h

RESOURCES += \
        resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


