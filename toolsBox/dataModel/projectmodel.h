#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <QObject>
#include "dataModel/datamodelbase.h"
#include "mySql/basicmysql.h"

class TOOLSBOXSHARED_EXPORT ProjectModel : public DataBaseModel<DbItem>
{
    Q_OBJECT
public:
    explicit ProjectModel(QString projectPath, DataModelBase *parent = nullptr);

    virtual void initTask();
    virtual void addTask();
    virtual void updataTask();
    virtual void removeTask();
    MOUNT_TYPE type(){ return MOUNT_PROJRCT; }
signals:

public slots:

private:
    QStringList findProjectNameList(QString projectPath); //查找项目目录下的工程文件

private:
    QString _projectPath;
    QStringList _projectFileList;
};

#endif // PROJECTMODEL_H
