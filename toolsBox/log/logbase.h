#ifndef LOGBASE_H
#define LOGBASE_H
#include <QObject>
#include "toolsBox_global.h"


enum LOG_LOCATION_TYPE
{
    PIntermVarGraph = Qt::UserRole +1,  //CIntermVarGraph
    PCInterfaceKIKOGraph                //PCInterfaceKIKOGraph
};

class TOOLSBOXSHARED_EXPORT LogBase : public QObject
{
    Q_OBJECT
public:
    LogBase(LOG_LOCATION_TYPE type, QObject *parent = nullptr);

    virtual void send() = 0;

protected:
    LOG_LOCATION_TYPE _type;
};

#endif // LOGBASE_H


