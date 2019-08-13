#ifndef VOLLEVELDB_H
#define VOLLEVELDB_H

#include "basicmysql.h"

class VolLevelDbItem : public DbItem
{
public:
    VolLevelDbItem():DbItem(), parentId(-1){}

    QString volType;    //电压级别
    int parentId;       //父对象ID
};
Q_DECLARE_METATYPE(VolLevelDbItem)


class TOOLSBOXSHARED_EXPORT VolLevelDb : public BasicMySql<VolLevelDbItem>
{
    Q_OBJECT
    VolLevelDb(QString fileName);
public:
    static VolLevelDb* bulid(QString fileName = "");
    QString tableName(){return "volLevel" /*QString("%1_%2").arg(TB_PREFIX).arg("VolLevel")*/;}

    /* ----------------[功能方法]--------------- */
    bool insertItem(const VolLevelDbItem& item); // 插入
    bool updateItem(const VolLevelDbItem& item); // 修改
protected:
    bool modifyItem(const VolLevelDbItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,VolLevelDbItem &item);
signals:

public slots:
};

#endif // VOLLEVELDB_H
