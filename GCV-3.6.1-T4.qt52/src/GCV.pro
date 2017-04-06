#-------------------------------------------------
#
# Project created by QtCreator 2012-02-13 T17:48:40
#
# Rename by LETARTARE  July 28, 2014
# GCV.pro
#
#-------------------------------------------------

TEMPLATE = app
TARGET = GrblController

DEFINES = QT_NO_DEBUG

QT   += core gui

unix {
   QT += widgets
}

# LETARTARE  June 12, 2014
contains(QT_VERSION, "^5.*") {
   QT *= widgets printsupport
}

# LETARTARE  July 28, 2014
# DESTDIR = bin

CONFIG(debug, debug|release) {
    #  TARGET =
    DESTDIR = bin/debug
    OBJECTS_DIR = build/debug/obj
    MOC_DIR = build/debug/moc
    RCC_DIR = build/debug/rcc
    UI_DIR = build/debug/ui
}
else {
  #  TARGET =
    DESTDIR = bin
    OBJECTS_DIR = build/release/obj
    MOC_DIR = build/release/moc
    RCC_DIR = build/release/rcc
    UI_DIR = build/release/ui
}

# QGlViewer
QT += xml opengl
#INCLUDEPATH += QGLViewer QGLWidget
# srichy  November 17, 2014
unix {
    !macx {
        LIBS += -lGLU
        LIBS += -lQGLViewer
    }

    linux-g++ {
      LIBS += -lqglviewer2
      message(Linux)
    }
}
else {
    LIBS += -lQGlViewer2
}


HEADER +=  visu3D/Point3D.h visu3D/Line3D.h visu3D/Arc3D.h visu3D/Tools3D.h  visu3D/Box3D.h
SOURCES += visu3D/Point3D.cpp visu3D/Line3D.cpp visu3D/Arc3D.cpp visu3D/Tools3D.cpp visu3D/Box3D.cpp


# Translations
	TRANSLATIONS += trlocale/GrblController_xx.ts
	TRANSLATIONS += trlocale/GrblController_fr.ts

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
    controlparams.cpp \
    visu3D/viewer3D.cpp

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
    version.h \
    visu3D/viewer3D.h

FORMS    += forms/mainwindow.ui \
    forms/options.ui \
    forms/grbldialog.ui \
    forms/about.ui

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


