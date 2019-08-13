#include "iedtemplatedb.h"

IedTemplateDb::IedTemplateDb(QString fileName)
{
    initDb(fileName);
}

IedTemplateDb *IedTemplateDb::bulid(QString fileName)
{
    static IedTemplateDb* sington = nullptr;
    if(fileName.isEmpty())
        return sington;

    if(sington == nullptr)
        sington = new IedTemplateDb(fileName);
    return sington;
}

bool IedTemplateDb::insertItem(const IedTemplateDbItem &item)
{
    QString cmd = "insert into %1 (name,desc,version,manufacturer,iedName,content,icdversion,icdcontent,createTime,updateTime) values(:name,:desc,:version,:manufacturer,:iedName,:content,:icdversion,:icdcontent,:createTime,:updateTime)";
    bool ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);
    return ret;
}

bool IedTemplateDb::updateItem(const IedTemplateDbItem &item)
{
    QString cmd = "update %1 set "
                  "name             = :name,"
                  "desc             = :desc,"
                  "version          = :version,"
                  "manufacturer     = :manufacturer,"
                  "iedName          = :iedName,"
                  "content          = :content,"
                  "icdversion       = :icdversion,"
                  "icdcontent       = :icdcontent,"
                  "updateTime       = :updateTime"
                  "where id         = :id";
    bool ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Update);
    return ret;
}

bool IedTemplateDb::modifyItem(const IedTemplateDbItem &item, const QString &cmd)
{
    bool ret = false;
    if(mDb) {
        QSqlQuery query(*mDb);
        query.prepare(cmd);
        query.bindValue(":id",              item.id);
        query.bindValue(":name",            item.name);
        query.bindValue(":desc",            item.desc);
        query.bindValue(":version",         item.version);
        query.bindValue(":manufacturer",    item.manufacturer);
        query.bindValue(":iedName",         item.iedName);
        query.bindValue(":content",         item.content);
        query.bindValue(":icdversion",      item.icdversion);
        query.bindValue(":icdcontent",      item.icdcontent);
        query.bindValue(":createTime",      QTime::currentTime());
        query.bindValue(":updateTime",      QTime::currentTime());
        ret = query.exec();
        if(!ret)
            throwError(query.lastError());
    }
    return ret;
}

void IedTemplateDb::selectItem(QSqlQuery &query, IedTemplateDbItem &item)
{
    item.id             = query.value("id").toInt();
    item.name           = query.value("name").toString();
    item.desc           = query.value("desc").toString();
    item.version        = query.value("version").toString();
    item.manufacturer   = query.value("manufacturer").toString();
    item.iedName        = query.value("iedName").toString();
    item.content        = query.value("content").toString();
    item.icdversion  = query.value("icdversion").toString();
    item.icdcontent     = query.value("icdcontent").toString();
    item.createTime     = query.value("createTime").toDateTime();
    item.updateTime     = query.value("updateTime").toDateTime();
}
