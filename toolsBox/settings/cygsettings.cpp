#include "CYGsettings.h"
#include <QCoreApplication>
#include <QTextCodec>

CYGSettings::CYGSettings(QObject *parent) : QObject(parent)
{
    QString customPath = getApplicationDirPath() + "/pack/system.ini";

    _cygSettings = new QSettings(customPath, QSettings::IniFormat);
    _cygSettings->setIniCodec(QTextCodec::codecForName("utf-8"));
    _cygSettings->beginGroup("system");
}

void CYGSettings::log(QString msg)
{
//    static QMutex mutex;
//    mutex.lock();
//    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz");
//    QString current_date = QString("(%1)").arg(current_date_time);
//    //QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);
//    QString message = QString("[%1]_ %3").arg(current_date).arg(msg);
//    QFile outFile1("logVideo1.txt");
//    QFile outFile2("logVideo2.txt");
//    outFile1.open(QIODevice::WriteOnly | QIODevice::Append);
//    if(outFile1.size() >= 1024*10 )
//    {
//        outFile1.close();
//        outFile2.remove();
//        QFile::copy("logVideo1.txt","logVideo2.txt");
//        outFile1.remove();
//        QFile outFile3("logVideo1.txt");
//        outFile3.open(QIODevice::WriteOnly | QIODevice::Append);
//        QTextStream text_stream(&outFile3);
//        text_stream << message << "\r\n";
//        outFile1.flush();
//        outFile1.close();
//    }
//    else
//    {
//        QTextStream text_stream(&outFile1);
//        text_stream << message << "\r\n";
//        outFile1.flush();
//        outFile1.close();
//    }
//    mutex.unlock();
}

QString CYGSettings::getApplicationDirPath()
{
    return QCoreApplication::applicationDirPath();
}

int CYGSettings::qtVersionCheck(int a, int b, int c)
{
    return QT_VERSION_CHECK(a, b, c);
}

void CYGSettings::setValue(const QString &key, const QVariant &value)
{
    _cygSettings->setValue(key, value);
}

void CYGSettings::setValue(const QString &key, const QVariant &value, const bool isSystem)
{
    if(!isSystem)
        return;
    QString customPath = getApplicationDirPath() + "/pack/system.ini";
    QSettings setSetting(customPath, QSettings::IniFormat);
    setSetting.setIniCodec(QTextCodec::codecForName("utf-8"));
    setSetting.beginGroup("system");
    setSetting.setValue(key,value);
}

QVariant CYGSettings::value(const QString &key, const QVariant &defaultValue)
{
    return _cygSettings->value(key, defaultValue);
}

QVariant CYGSettings::getvalue(const QString &key, const QVariant &defaultValue)
{
    QString customPath = getApplicationDirPath() + "/pack/system.ini";
    QSettings readSetting(customPath, QSettings::IniFormat);
    readSetting.setIniCodec(QTextCodec::codecForName("utf-8"));
    readSetting.beginGroup("system");
    return readSetting.value(key, defaultValue);
}

QVariant CYGSettings::dValue(const QString &key, const QVariant &defaultValue, const QString &beginGroup)
{
    QSettings settings;
    settings.beginGroup(beginGroup);
    return settings.value(key,defaultValue).toString();
}

QVariant CYGSettings::dValue(const QString &key, const QVariant &defaultValue, const QString &beginGroup, bool isSystem)
{
    isSystem = isSystem;    //remove warning
    QSettings settings;
    settings.beginGroup(beginGroup);
    return settings.value(key,defaultValue).toString();
}

void CYGSettings::dSetValue(const QString &key, const QVariant &value, const QString &beginGroup)
{
    QSettings settings;
    settings.beginGroup(beginGroup);
    settings.setIniCodec(QTextCodec::codecForName("utf-8"));
    settings.setValue(key,value);
}

void CYGSettings::dSetValue(const QString &key, const QVariant &value, const QString &beginGroup, bool isSystem)
{
    isSystem = isSystem;    // remove warning
    QSettings settings;
    settings.beginGroup(beginGroup);
    settings.setIniCodec(QTextCodec::codecForName("utf-8"));
    settings.setValue(key,value);
}


