#include "substationdb.h"

SubstationDb::SubstationDb(QString fileName)
{
    initDb(fileName);
}

SubstationDb *SubstationDb::bulid(QString fileName)
{
    static SubstationDb* sington = nullptr;
    if(fileName.isEmpty())
        return sington;

    if(sington == nullptr)
        sington = new SubstationDb(fileName);
    return sington;
}

bool SubstationDb::insertItem(const SubstationDbItem &item)
{
    QString cmd = "insert into %1 (name,desc,createTime,updateTime) values(:name,:desc,:createTime,:updateTime)";
    bool ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);
    return ret;
}

bool SubstationDb::updateItem(const SubstationDbItem &item)
{
    QString cmd = "update %1 set "
                  "name         = :name,"
                  "desc         = :desc,"
                  "updateTime   = :updateTime"
                  "where id     = :id";
    bool ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Update);
    return ret;
}

bool SubstationDb::modifyItem(const SubstationDbItem &item, const QString &cmd)
{
    bool ret = false;
    if(mDb) {
        QSqlQuery query(*mDb);
        query.prepare(cmd);
        query.bindValue(":id",item.id);
        query.bindValue(":name",item.name);
        query.bindValue(":desc",item.desc);
        query.bindValue(":createTime", QTime::currentTime());
        query.bindValue(":updateTime", QTime::currentTime());
        ret = query.exec();
        if(!ret)
            throwError(query.lastError());
    }
    return ret;
}

void SubstationDb::selectItem(QSqlQuery &query, SubstationDbItem &item)
{
    item.id         = query.value("id").toInt();
    item.name       = query.value("name").toString();
    item.desc       = query.value("desc").toString();
    item.createTime = query.value("createTime").toDateTime();
    item.updateTime = query.value("updateTime").toDateTime();
}
