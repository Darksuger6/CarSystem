QT       += core gui network \
            xml \
            multimedia \
            multimediawidgets \
            widgets \
            sql \
            serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

win32-msvc {
    QMAKE_CXXFLAGS += /utf-8
    QMAKE_CFLAGS   += /utf-8
}

INC_ROOT = $$PWD/inc

INCLUDEPATH += \
    $$INC_ROOT

SOURCES += \
    src/Audio.cpp \
    src/buzzer.cpp \
    src/citycodeutils.cpp \
    src/day.cpp \
    src/dht11.cpp \
    src/hardware.cpp \
    src/led.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/map.cpp \
    src/mq135.cpp \
    src/player.cpp \
    src/playercontrols.cpp \
    src/playlistmodel.cpp \
    src/rotatablewidget.cpp \
    src/simplemessagebox.cpp \
    src/sr04.cpp \
    src/videowidget.cpp \
    src/weather.cpp

HEADERS += \
    inc/Audio.h \
    inc/buzzer.h \
    inc/citycodeutils.h \
    inc/commonhelper.h \
    inc/day.h \
    inc/dht11.h \
    inc/hardware.h \
    inc/led.h \
    inc/mainwindow.h \
    inc/map.h \
    inc/mq135.h \
    inc/player.h \
    inc/playercontrols.h \
    inc/playlistmodel.h \
    inc/rotatablewidget.h \
    inc/simplemessagebox.h \
    inc/sr04.h \
    inc/videowidget.h \
    inc/weather.h

FORMS += \
    Audio.ui \
    hardware.ui \
    mainwindow.ui \
    map.ui \
    rotatablewidget.ui \
    weather.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DEFINES += QT_DEPRECATED_WARNINGS