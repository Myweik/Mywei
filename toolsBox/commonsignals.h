#ifndef COMMONSIGNALS_H
#define COMMONSIGNALS_H
#include <QDebug>
#include <QObject>
#include "toolsBox_global.h"
#include "log/logbase.h"
#include "dataModel/datamodelbase.h"

class TOOLSBOXSHARED_EXPORT CommonSignals : public QObject
{
    Q_OBJECT
public:
    CommonSignals(QObject *parent = nullptr);

signals:
    void sendAddTask(Data_Task_TYPE type ,DataModelBase* data);

//    void sendEnDisLNFunc(void* iedLn); //CIedLNode 强转此类
//    void sendLogLocation(void *ied, void *lnode, LOG_LOCATION_TYPE type); //CIed CIedLNode 强转此类
//    void sendSwitchDockState(); //切换dock的显示状态等

public slots:
};

#endif // COMMONSIGNALS_H
