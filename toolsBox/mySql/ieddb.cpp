#include "ieddb.h"

IedDb::IedDb(QString fileName)
{
    initDb(fileName);
}

IedDb *IedDb::bulid(QString fileName)
{
    static IedDb* sington = nullptr;
    if(fileName.isEmpty())
        return sington;

    if(sington == nullptr)
        sington = new IedDb(fileName);
    return sington;
}

bool IedDb::insertItem(const IedDbItem &item)
{
    QString cmd = "insert into %1 (name,desc,configVersion,runVersion,manufacturer,type,iedNode,iedNameByUser,parentId,createTime,updateTime) values(:name,:desc,:configVersion,:runVersion,:manufacturer,:type,:iedNode,:iedNameByUser,:parentId,:createTime,:updateTime)";
    bool ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);
    return ret;
}

bool IedDb::updateItem(const IedDbItem &item)
{
    QString cmd = "update %1 set "
                  "name             = :name,"
                  "desc             = :desc,"
                  "configVersion    = :configVersion,"
                  "runVersion       = :runVersion,"
                  "manufacturer     = :manufacturer,"
                  "type             = :type,"
                  "iedNode          = :iedNode,"
                  "iedNameByUser    = :iedNameByUser,"
                  "parentId         = :parentId,"
                  "updateTime       = :updateTime"
                  "where id         = :id";
    bool ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Update);
    return ret;
}

bool IedDb::modifyItem(const IedDbItem &item, const QString &cmd)
{
    bool ret = false;
    if(mDb) {
        QSqlQuery query(*mDb);
        query.prepare(cmd);
        query.bindValue(":id",              item.id);
        query.bindValue(":name",            item.name);
        query.bindValue(":desc",            item.desc);
        query.bindValue(":configVersion",   item.configVersion);
        query.bindValue(":runVersion",      item.runVersion);
        query.bindValue(":manufacturer",    item.manufacturer);
        query.bindValue(":type",            item.type);
        query.bindValue(":iedNode",         item.iedNode);
        query.bindValue(":iedNameByUser",   item.iedNameByUser);
        query.bindValue(":parentId",        item.parentId);
        query.bindValue(":createTime",      QTime::currentTime());
        query.bindValue(":updateTime",      QTime::currentTime());
        ret = query.exec();
        if(!ret)
            throwError(query.lastError());
    }
    return ret;
}

void IedDb::selectItem(QSqlQuery &query, IedDbItem &item)
{
    item.id             = query.value("id").toInt();
    item.name           = query.value("name").toString();
    item.desc           = query.value("desc").toString();
    item.configVersion  = query.value("configVersion").toString();
    item.runVersion     = query.value("runVersion").toString();
    item.manufacturer   = query.value("manufacturer").toString();
    item.type           = query.value("type").toString();
    item.iedNode        = query.value("iedNode").toString();
    item.iedNameByUser  = query.value("iedNameByUser").toString();
    item.parentId       = query.value("parentId").toInt();
    item.createTime     = query.value("createTime").toDateTime();
    item.updateTime     = query.value("updateTime").toDateTime();
}
