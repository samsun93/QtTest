QT += core
TEMPLATE = app
CONFIG += console c++14
#CONFIG -= app_bundle
#CONFIG -= qt


SOURCES += \
        main.cpp

include($$PWD/JsonSrc.pri)
include($$PWD/qt-json/qt-json.pri)
#  example.cpp

