#include "sqlmanager.h"
#include "settings/cygsettings.h"

/* ----------------------------[SqlManager]------------------------------- */
SqlManager::SqlManager(QObject *parent) : QObject(parent)
{
    QString systemDbPath = CYGSettings::getvalue("app/BaseDBPath", "pack/CYGSystem.prj").toString();
    set_userDb(UserDb::bulid(systemDbPath));
    set_iedTemplateDb(IedTemplateDb::bulid(systemDbPath));
}

SqlManager::~SqlManager()
{   
    delete userDb();
    delete iedTemplateDb();
}

bool SqlManager::containPro(QString fileName)
{
    return !fileName.isEmpty() && !_proSqlMap.keys().contains(fileName);
}

bool SqlManager::openPro(QString fileName)
{
    if(containPro(fileName)){
        _proSqlMap[fileName] = new ProjectSql(fileName, this);
        return true;
    }
    return false;
}

ProjectSql *SqlManager::findPro(QString fileName)
{
    ProjectSql *proSql = nullptr;
    if(containPro(fileName)){
       proSql = _proSqlMap[fileName];
    }
    return proSql;
}

/* ----------------------------[ProjectSql]------------------------------- */
ProjectSql::ProjectSql(QString fileName, QObject *parent)
    : QObject(parent)
    , _flieName(fileName)
{
    set_substationDb(SubstationDb::bulid(fileName));
    set_volLevelDb(VolLevelDb::bulid(fileName));
    set_bayDb(BayDb::bulid(fileName));
    set_iedDb(IedDb::bulid(fileName));
}

ProjectSql::~ProjectSql()
{
//    delete substationDb();
//    delete volLevelDb();
//    delete bayDb();
//    delete iedDb();
}
