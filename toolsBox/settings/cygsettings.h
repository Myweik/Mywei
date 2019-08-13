#ifndef CYGSETTINGS_H
#define CYGSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QDir>
#include <QVariant>

#include "toolsBox_global.h"

class TOOLSBOXSHARED_EXPORT CYGSettings : public QObject
{
    Q_OBJECT
public:
    CYGSettings(QObject *parent = 0);

    /* 调试用 写文件 */
    Q_INVOKABLE void log(QString meg);
    /* 获取当前软件路径 */
    Q_INVOKABLE static QString getApplicationDirPath();
    /* 获取Qt版本  QT_VERSION >= QT_VERSION_CHECK(5, 10, 0) */
    Q_INVOKABLE int qtVersion(){ return QT_VERSION; }
    Q_INVOKABLE int qtVersionCheck(int a, int b, int c); //生成版本号

    /* system.ini */
    Q_INVOKABLE void setValue(const QString &key, const QVariant &value);
    static void setValue(const QString &key, const QVariant &value, const bool isSystem);
    Q_INVOKABLE QVariant value(const QString &key, const QVariant &defaultValue);
    static  QVariant getvalue(const QString &key, const QVariant &defaultValue);

    /* cache */
    //默认路径配置数据中读取数据
    Q_INVOKABLE QVariant dValue(const QString &key, const QVariant &defaultValue,const QString &beginGroup);
    static QVariant dValue(const QString &key, const QVariant &defaultValue,const QString &beginGroup,bool isSystem);
    //默认路径配置数据中写入数据
    Q_INVOKABLE void dSetValue(const QString &key, const QVariant &value,const QString &beginGroup);
    static void dSetValue(const QString &key, const QVariant &value,const QString &beginGroup,bool isSystem);

signals:

public slots:

private:
    QSettings *_cygSettings;
};

#endif // CYGSETTINGS_H
