QT += qml

HEADERS += \
    $$PWD/toolsbox.h \
    $$PWD/commonsignals.h \
    $$PWD/qmlcommon.h \


SOURCES += \
    $$PWD/toolsbox.cpp \
    $$PWD/commonsignals.cpp \

include($$PWD/log/log.pri)
include($$PWD/mySql/mySql.pri)
include($$PWD/settings/settings.pri)
include($$PWD/thread/thread.pri)
