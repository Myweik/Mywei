#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QObject>
#include "toolsBox_global.h"
#include "qmlcommon.h"

#include "iedtemplatedb.h"
#include "userdb.h"

#include "substationdb.h"
#include "volleveldb.h"
#include "baydb.h"
#include "ieddb.h"

class ProjectSql;

class TOOLSBOXSHARED_EXPORT SqlManager : public QObject
{
    Q_OBJECT
    /* ---------------------[系统级]----------------------- */
    GENERATE_QML_PROPERTY(userDb, UserDb*, "UserDb")
    GENERATE_QML_PROPERTY(iedTemplateDb, IedTemplateDb*, "IedTemplateDb")
public:
    explicit SqlManager(QObject *parent = nullptr);
    ~SqlManager();

    bool containPro(QString fileName);
    bool openPro(QString fileName);
    ProjectSql* findPro(QString fileName);
signals:

public slots:

private:
    QMap<QString, ProjectSql*> _proSqlMap;
};

class TOOLSBOXSHARED_EXPORT ProjectSql : public QObject
{
    Q_OBJECT
    /* ---------------------[用户级]----------------------- */
    GENERATE_QML_PROPERTY(substationDb, SubstationDb*, "SubstationDb")
    GENERATE_QML_PROPERTY(volLevelDb, VolLevelDb*, "VolLevelDb")
    GENERATE_QML_PROPERTY(bayDb, BayDb*, "BayDb")
    GENERATE_QML_PROPERTY(iedDb, IedDb*, "IedDb")
public:
    ProjectSql(QString fileName, QObject *parent = nullptr);
    ~ProjectSql();
signals:

public slots:

private:
    QString _flieName;
};


#endif // SQLMANAGER_H
