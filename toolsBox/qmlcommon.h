#ifndef QMLCOMMON_H
#define QMLCOMMON_H

#include <QtQml/QQmlEngine>
#include <QString>

#define GENERATE_QML_PROPERTY(Name,Type,comment) \
    public : \
Q_PROPERTY(Type Name READ Name WRITE set_##Name NOTIFY Name##Changed) \
Q_PROPERTY(QString Name##Comment READ Name##Comment CONSTANT) \
    private : \
        Type _##Name; \
    public : \
        Type Name() const{return _##Name;} \
        void set_##Name(Type value){ if(_##Name == value) return; \
            _##Name = value; \
         emit Name##Changed(); } \
        QString Name##Comment() const{return tr(comment);} \
    Q_SIGNALS : \
        void Name##Changed();

#define GENERATE_QML_PROPERTY_ONSET(Name,Type,comment) \
    public : \
Q_PROPERTY(Type Name READ Name WRITE set_##Name NOTIFY Name##Changed) \
Q_PROPERTY(QString Name##Comment READ Name##Comment CONSTANT) \
    private : \
        Type _##Name; \
    public : \
        Type Name() const{return _##Name;} \
        void set_##Name(Type value); \
        QString Name##Comment() const{return tr(comment);} \
    Q_SIGNALS : \
        void Name##Changed();

#endif // QMLCOMMON_H
