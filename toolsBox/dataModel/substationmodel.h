#ifndef SUBSTATIONMODEL_H
#define SUBSTATIONMODEL_H

#include <QObject>
#include "dataModel/datamodelbase.h"
#include "mySql/substationdb.h"

class TOOLSBOXSHARED_EXPORT SubstationModel : public DataBaseModel<SubstationDbItem>
{
    Q_OBJECT
public:
    explicit SubstationModel(SubstationDbItem data, DataModelBase *parent = nullptr);

    virtual void initTask();
    virtual void addTask();
    virtual void updataTask();
    virtual void removeTask();
    MOUNT_TYPE type(){ return MOUNT_SUBSTATION; }
signals:

public slots:
};

#endif // SUBSTATIONMODEL_H
