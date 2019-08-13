#-------------------------------------------------
#
# Project created by QtCreator 2019-08-01T14:29:54
#
#-------------------------------------------------

QT       += qml core

QT       -= gui

TARGET = toolsBox
TEMPLATE = lib
DESTDIR  = $$PWD/../bin/libs

DEFINES += TOOLSBOX_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

    CONFIG(release,debug|release) {
        TARGET = toolsBox
    }
    CONFIG(debug,debug|release) {
        TARGET = toolsBox_d
    }


HEADERS += \
        toolsbox_global.h \ 

# 单例工具
include(toolsBox.pri)
# 数据模型
include($$PWD/dataModel/dataModel.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug,debug|release) {
    CONFIG += console
}

