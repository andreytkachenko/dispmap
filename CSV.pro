#-------------------------------------------------
#
# Project created by QtCreator 2014-07-10T12:35:18
#
#-------------------------------------------------

QT += core gui qml quick widgets
TEMPLATE = app

TARGET = CSV
CONFIG += c++11
CONFIG += j4
CONFIG -= console

SOURCES += main.cpp \
    svimage.cpp \
    svworker.cpp \
    svprocessor.cpp \
    svkernelv1.cpp \
    svkernelv2.cpp \
    svimageprovider.cpp \
    svpoint.cpp \
    svcurve.cpp \
    svsimplepoint.cpp \
    svfigure.cpp \
    svobject.cpp

HEADERS += \
    svimage.h \
    svworker.h \
    svprocessor.h \
    svabstractkernel.h \
    svkernelv1.h \
    svkernelv2.h \
    svimageprovider.h \
    svpoint.h \
    svcurve.h \
    svsimplepoint.h \
    svfigure.h \
    svobject.h

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    Main.qml
