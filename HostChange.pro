#-------------------------------------------------
#
# Project created by QtCreator 2016-08-28T19:35:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HostChange
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    asktabname.cpp \
    tabofhosts.cpp \
    patternparser.cpp

HEADERS  += mainwindow.h \
    asktabname.h \
    tabofhosts.h \
    patternparser.h

FORMS    += mainwindow.ui \
    asktabname.ui

DISTFILES += \
    README.md

ject.pro

unix:!mac {
 LIBS += -Wl,-rpath=\\\$$ORIGIN/../lib
}

target.path = /usr/share/host_change/bin
target.files = HostChange qt.conf
INSTALLS += target
data.path = /usr/share/host_change/lib
data.files = lib/*
INSTALLS += data
