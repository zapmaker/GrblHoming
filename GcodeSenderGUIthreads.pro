#-------------------------------------------------
#
# Project created by QtCreator 2012-02-13 T17:48:40
#
# (fourth axis modifications and translation added by LETARTARE 2013-08-03)
#-------------------------------------------------

QT       += core gui widgets

TARGET = GrblController
TEMPLATE = app

include(QextSerialPort/qextserialport.pri)
include(log4qt/log4qt.pri)


SOURCES += main.cpp\
        mainwindow.cpp \
    rs232.cpp \
    options.cpp \
    grbldialog.cpp \
    about.cpp \
    gcode.cpp \
    timer.cpp \
    atomicintbool.cpp \
    coord3d.cpp \
    renderarea.cpp \
    positem.cpp \
    renderitemlist.cpp \
    lineitem.cpp \
    itemtobase.cpp \
    arcitem.cpp \
    pointitem.cpp \
    controlparams.cpp

HEADERS  += mainwindow.h \
    rs232.h \
    options.h \
    grbldialog.h \
    definitions.h \
    about.h \
    images.rcc \
    gcode.h \
    timer.h \
    atomicintbool.h \
    coord3d.h \
    log4qtdef.h \
    renderarea.h \
    positem.h \
    renderitemlist.h \
    lineitem.h \
    itemtobase.h \
    arcitem.h \
    pointitem.h \
    termiosext.h \
    controlparams.h \
    version.h

FORMS    += mainwindow.ui \
    options.ui \
    grbldialog.ui \
    about.ui

RESOURCES += GrblController.qrc

RC_FILE = grbl.rc

OTHER_FILES += \
    android/AndroidManifest.xml \
    android/res/drawable/icon.png \
    android/res/drawable/logo.png \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-mdpi/icon.png \
    android/res/layout/splash.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/origo/QtActivity.java \
    android/src/org/kde/necessitas/origo/QtApplication.java \
    android/version.xml

# Translations
	TRANSLATIONS += trlocale/GrblController_xx.ts
	TRANSLATIONS += trlocale/GrblController_fr.ts
