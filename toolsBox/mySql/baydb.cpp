#include "baydb.h"

BayDb::BayDb(QString fileName)
{
    initDb(fileName);
}

BayDb *BayDb::bulid(QString fileName)
{
    static BayDb* sington = nullptr;
    if(fileName.isEmpty())
        return sington;

    if(sington == nullptr)
        sington = new BayDb(fileName);
    return sington;
}

bool BayDb::insertItem(const BayDbItem &item)
{
    QString cmd = "insert into %1 (name,desc,parentId,createTime,updateTime) values(:name,:desc,:parentId,:createTime,:updateTime)";
    bool ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);
    return ret;
}

bool BayDb::updateItem(const BayDbItem &item)
{
    QString cmd = "update %1 set "
                  "name         = :name,"
                  "desc         = :desc,"
                  "parentId     = :parentId,"
                  "updateTime   = :updateTime"
                  "where id     = :id";
    bool ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Update);
    return ret;
}

bool BayDb::modifyItem(const BayDbItem &item, const QString &cmd)
{
    bool ret = false;
    if(mDb) {
        QSqlQuery query(*mDb);
        query.prepare(cmd);
        query.bindValue(":id",item.id);
        query.bindValue(":name",item.name);
        query.bindValue(":desc",item.desc);
        query.bindValue(":parentId",item.parentId);
        query.bindValue(":createTime", QTime::currentTime());
        query.bindValue(":updateTime", QTime::currentTime());
        ret = query.exec();
        if(!ret)
            throwError(query.lastError());
    }
    return ret;
}

void BayDb::selectItem(QSqlQuery &query, BayDbItem &item)
{
    item.id         = query.value("id").toInt();
    item.name       = query.value("name").toString();
    item.desc       = query.value("desc").toString();
    item.parentId   = query.value("parentId").toInt();
    item.createTime = query.value("createTime").toDateTime();
    item.updateTime = query.value("updateTime").toDateTime();
}
