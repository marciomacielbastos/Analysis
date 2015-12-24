QT += core
QT -= gui

CONFIG += c++11

TARGET = Analysis
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    csvmanager.h \
    kernel.h \
    subunit.h \
    point.h \
    unit.h \
    realestate.h
