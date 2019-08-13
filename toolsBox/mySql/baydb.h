#ifndef BAYDB_H
#define BAYDB_H

#include "basicmysql.h"

class BayDbItem : public DbItem
{
public:
    BayDbItem():DbItem(), parentId(-1){}

    int parentId;       //父对象ID
};
Q_DECLARE_METATYPE(BayDbItem)


class TOOLSBOXSHARED_EXPORT BayDb : public BasicMySql<BayDbItem>
{
    Q_OBJECT
    BayDb(QString fileName);
public:
    static BayDb *bulid(QString fileName = "");
    QString tableName(){return "bay" /*QString("%1_%2").arg(TB_PREFIX).arg("Bay")*/;}

    /* ----------------[功能方法]--------------- */
    bool insertItem(const BayDbItem& item); // 插入
    bool updateItem(const BayDbItem& item); // 修改
protected:
    bool modifyItem(const BayDbItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,BayDbItem &item);
signals:

public slots:
};

#endif // BAYDB_H
