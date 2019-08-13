#ifndef TOOLSBOX_H
#define TOOLSBOX_H

#include "toolsbox_global.h"
#include "qmlcommon.h"

#include "toolsBox_global.h"
class CommonSignals;
class SqlManager;
class SqlThread;

class TOOLSBOXSHARED_EXPORT ToolsBox : public QObject
{
    Q_OBJECT
GENERATE_QML_PROPERTY(commonSignals, CommonSignals*, "CommonSignals")
GENERATE_QML_PROPERTY(sqlManager, SqlManager*, "SqlManager")
GENERATE_QML_PROPERTY(sqlThread, SqlThread*, "SqlThread")
public:
    static ToolsBox*  getInstance();

signals:
public slots:

private:
    ToolsBox(QObject *parent = nullptr);
    //把复制构造函数和=操作符也设为私有,防止被复制
    ToolsBox(const ToolsBox&) = delete;
    ToolsBox& operator=(const ToolsBox&) = delete;

private:
    static ToolsBox*  _toolsBox;
};

#endif // TOOLSBOX_H
