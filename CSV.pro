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
    svimageprovider.cpp \
    svpoint.cpp \
    svcurve.cpp \
    svsimplepoint.cpp \
    svfigure.cpp \
    svobject.cpp \
    svpointcloud.cpp \
    svkernel.cpp \
    svpointcloudviewer.cpp \
    svapplicationcontext.cpp

HEADERS += \
    svimage.h \
    svworker.h \
    svprocessor.h \
    svimageprovider.h \
    svpoint.h \
    svcurve.h \
    svsimplepoint.h \
    svfigure.h \
    svobject.h \
    svpointcloud.h \
    svdefs.h \
    svkernel.h \
    svpointcloudviewer.h \
    svapplicationcontext.h

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    Main.qml
