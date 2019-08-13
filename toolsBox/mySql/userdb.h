#ifndef USERDB_H
#define USERDB_H

#include "basicmysql.h"

enum USER_LEVEL
{
     USER_LEVEL0 = 0  //访问级0（只读-部分可见）
    ,USER_LEVEL1      //访问级1（只读-全部可见）
    ,USER_LEVEL2      //一般级0（部分可见可写）
    ,USER_LEVEL3      //一般级1（全部可见 部分可写）
    ,USER_LEVEL4      //管理级 （全部可见可写）
};

class UserDbItem : public DbItem
{
public:
    UserDbItem():DbItem(){}

    QString password;   //密码
    USER_LEVEL type;    //权限
};
Q_DECLARE_METATYPE(UserDbItem)


class TOOLSBOXSHARED_EXPORT UserDb : public BasicMySql<UserDbItem>
{
    Q_OBJECT
    UserDb(QString fileName);
public:
    static UserDb *bulid(QString fileName = "");
    QString tableName(){return "user" /*QString("%1_%2").arg(TB_PREFIX).arg("User")*/;}

    /* ----------------[功能方法]--------------- */
    bool insertItem(const UserDbItem& item); // 插入
    bool updateItem(const UserDbItem& item); // 修改
protected:
    bool modifyItem(const UserDbItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,UserDbItem &item);
signals:

public slots:
};


#endif // USERDB_H
