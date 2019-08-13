#ifndef SUBSTATIONDB_H
#define SUBSTATIONDB_H

#include "basicmysql.h"

class SubstationDbItem : public DbItem
{
public:
    SubstationDbItem():DbItem() {}
};
Q_DECLARE_METATYPE(SubstationDbItem)


class TOOLSBOXSHARED_EXPORT SubstationDb : public BasicMySql<SubstationDbItem>
{
    Q_OBJECT
    SubstationDb(QString fileName);
public:
    static SubstationDb* bulid(QString fileName = "");
    QString tableName(){return "substation"/*QString("%1_%2").arg(TB_PREFIX).arg("Substation")*/;}

    /* ----------------[功能方法]--------------- */
    bool insertItem(const SubstationDbItem& item); // 插入
    bool updateItem(const SubstationDbItem& item); // 修改
protected:
    bool modifyItem(const SubstationDbItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,SubstationDbItem &item);
signals:

public slots:
};

#endif // SUBSTATIONDB_H
