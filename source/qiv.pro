QT += core gui widgets

TARGET = qiv
TEMPLATE = app
DESTDIR = ./output

CONFIG += c++17
# Before Qt 5.11 we need the following too
unix:QMAKE_CXXFLAGS += -std=c++17

INCLUDEPATH += .

HEADERS += \
    ColorMap.h  \
    ImageFormat.h \
    ImageType.h \
    ImageWindow.h \
    ViewDataInterface.h \
    ImageData.h \
    ImageScrollArea.h \
    ImageView.h \
    MainWindow.h

SOURCES += \
    ColorMap.cpp  \
    ImageScrollArea.cpp \
    ImageWindow.cpp \
    ImageData.cpp \
    ImageType.cpp \
    main.cpp  \
    ImageFormat.cpp \
    ImageView.cpp \
    MainWindow.cpp

FORMS += \
  MainWindow.ui
