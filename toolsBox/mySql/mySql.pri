QT += sql

INCLUDEPATH += $$PWD/..

SOURCES += \
    $$PWD/basicmysql.cpp \
    $$PWD/substationdb.cpp \
    $$PWD/volleveldb.cpp \
    $$PWD/baydb.cpp \
    $$PWD/ieddb.cpp \
    $$PWD/sqlmanager.cpp \
    $$PWD/iedtemplatedb.cpp \
    $$PWD/userdb.cpp

HEADERS += \
    $$PWD/basicmysql.h \
    $$PWD/substationdb.h \
    $$PWD/volleveldb.h \
    $$PWD/baydb.h \
    $$PWD/ieddb.h \
    $$PWD/sqlmanager.h \
    $$PWD/iedtemplatedb.h \
    $$PWD/userdb.h
