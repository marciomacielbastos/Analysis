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
    subunit.h \
    point.h \
    unit.h \
    interpolchain.h \
    spline.h \
    matrix.h \
    lagrange.h \
    thread_bucket.h \
    real_estate.h
