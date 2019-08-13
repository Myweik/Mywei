#include "volleveldb.h"

VolLevelDb::VolLevelDb(QString fileName)
{
    initDb(fileName);
}

VolLevelDb *VolLevelDb::bulid(QString fileName)
{
    static VolLevelDb* sington = nullptr;
    if(fileName.isEmpty())
        return sington;

    if(sington == nullptr)
        sington = new VolLevelDb(fileName);
    return sington;
}

bool VolLevelDb::insertItem(const VolLevelDbItem &item)
{
    QString cmd = "insert into %1 (name,desc,volType,parentId,createTime,updateTime) values(:name,:desc,:volType,:parentId,:createTime,:updateTime)";
    bool ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);
    return ret;
}

bool VolLevelDb::updateItem(const VolLevelDbItem &item)
{
    QString cmd = "update %1 set "
                  "name         = :name,"
                  "desc         = :desc,"
                  "volType      = :volType,"
                  "parentId     = :parentId,"
                  "updateTime   = :updateTime"
                  "where id     = :id";
    bool ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Update);
    return ret;
}

bool VolLevelDb::modifyItem(const VolLevelDbItem &item, const QString &cmd)
{
    bool ret = false;
    if(mDb) {
        QSqlQuery query(*mDb);
        query.prepare(cmd);
        query.bindValue(":id",item.id);
        query.bindValue(":name",item.name);
        query.bindValue(":desc",item.desc);
        query.bindValue(":volType",item.volType);
        query.bindValue(":parentId",item.parentId);
        query.bindValue(":createTime", QTime::currentTime());
        query.bindValue(":updateTime", QTime::currentTime());
        ret = query.exec();
        if(!ret)
            throwError(query.lastError());
    }
    return ret;
}

void VolLevelDb::selectItem(QSqlQuery &query, VolLevelDbItem &item)
{
    item.id         = query.value("id").toInt();
    item.name       = query.value("name").toString();
    item.desc       = query.value("desc").toString();
    item.volType    = query.value("volType").toString();
    item.parentId   = query.value("parentId").toInt();
    item.createTime = query.value("createTime").toDateTime();
    item.updateTime = query.value("updateTime").toDateTime();
}
