#include "userdb.h"

UserDb::UserDb(QString fileName)
{
    initDb(fileName);
}

UserDb *UserDb::bulid(QString fileName)
{
    static UserDb* sington = nullptr;
    if(fileName.isEmpty())
        return sington;

    if(sington == nullptr)
        sington = new UserDb(fileName);
    return sington;
}

bool UserDb::insertItem(const UserDbItem &item)
{
    QString cmd = "insert into %1 (name,desc,password,type,createTime,updateTime) values(:name,:desc,:password,:type:createTime,:updateTime)";
    bool ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);
    return ret;
}

bool UserDb::updateItem(const UserDbItem &item)
{
    QString cmd = "update %1 set "
                  "name         = :name,"
                  "desc         = :desc,"
                  "password     = :password,"
                  "type         = :type,"
                  "updateTime   = :updateTime"
                  "where id     = :id";
    bool ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Update);
    return ret;
}

bool UserDb::modifyItem(const UserDbItem &item, const QString &cmd)
{
    bool ret = false;
    if(mDb) {
        QSqlQuery query(*mDb);
        query.prepare(cmd);
        query.bindValue(":id",          item.id);
        query.bindValue(":name",        item.name);
        query.bindValue(":desc",        item.desc);
        query.bindValue(":password",    item.password);
        query.bindValue(":type",        item.type);
        query.bindValue(":createTime",  QTime::currentTime());
        query.bindValue(":updateTime",  QTime::currentTime());
        ret = query.exec();
        if(!ret)
            throwError(query.lastError());
    }
    return ret;
}

void UserDb::selectItem(QSqlQuery &query, UserDbItem &item)
{
    item.id         = query.value("id").toInt();
    item.name       = query.value("name").toString();
    item.desc       = query.value("desc").toString();
    item.password   = query.value("password").toString();
    item.type       = (USER_LEVEL)query.value("type").toInt();
    item.createTime = query.value("createTime").toDateTime();
    item.updateTime = query.value("updateTime").toDateTime();
}
