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
    $$INC_ROOT \
    $$INC_ROOT/app \
    $$INC_ROOT/dev_app

SOURCES += \
    src/main.cpp \
    src/app/Audio.cpp \
    src/app/citycodeutils.cpp \
    src/app/day.cpp \
    src/app/mainwindow.cpp \
    src/app/map.cpp \
    src/app/player.cpp \
    src/app/playercontrols.cpp \
    src/app/playlistmodel.cpp \
    src/app/rotatablewidget.cpp \
    src/app/simplemessagebox.cpp \
    src/app/videowidget.cpp \
    src/app/weather.cpp \
    src/dev_app/hardware.cpp \
    src/dev_app/buzzer.cpp \
    src/dev_app/dht11.cpp \
    src/dev_app/led.cpp \
    src/dev_app/sr04.cpp \
    src/dev_app/mq135.cpp \

HEADERS += \
    inc/app/Audio.h \
    inc/app/citycodeutils.h \
    inc/app/commonhelper.h \
    inc/app/day.h \
    inc/app/mainwindow.h \
    inc/app/map.h \
    inc/app/player.h \
    inc/app/playercontrols.h \
    inc/app/playlistmodel.h \
    inc/app/rotatablewidget.h \
    inc/app/simplemessagebox.h \
    inc/app/videowidget.h \
    inc/app/weather.h \
    inc/dev_app/hardware.h \
    inc/dev_app/buzzer.h \
    inc/dev_app/dht11.h \
    inc/dev_app/led.h \
    inc/dev_app/sr04.h \
    inc/dev_app/mq135.h \

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
