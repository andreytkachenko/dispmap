#-------------------------------------------------
#
# Project created by QtCreator 2014-07-10T12:35:18
#
#-------------------------------------------------

QT += core qml
TEMPLATE = app

TARGET = CSV
CONFIG += c++11
CONFIG -= console

SOURCES += main.cpp \
    svimage.cpp \
    svworker.cpp \
    svprocessor.cpp \
    svkernelv1.cpp \
    svkernelv2.cpp \
    svimageprovider.cpp

HEADERS += \
    svimage.h \
    svworker.h \
    svprocessor.h \
    svabstractkernel.h \
    svkernelv1.h \
    svkernelv2.h \
    svimageprovider.h

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    Main.qml
