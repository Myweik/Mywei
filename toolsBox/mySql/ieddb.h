#ifndef IEDDB_H
#define IEDDB_H

#include "basicmysql.h"

class IedDbItem : public DbItem
{
public:
    IedDbItem():DbItem(), parentId(-1){}

    QString configVersion;  //配置版本
    QString runVersion;     //运行版本
    QString manufacturer;   //制造商
    QString type;           //所属模板 - 型号
    QString iedNode;        //xml数据
    QString iedNameByUser;
    int parentId;           //父对象ID
};
Q_DECLARE_METATYPE(IedDbItem)


class TOOLSBOXSHARED_EXPORT IedDb : public BasicMySql<IedDbItem>
{
    Q_OBJECT
    IedDb(QString fileName);
public:
    static IedDb *bulid(QString fileName = "");
    QString tableName(){return "ied" /*QString("%1_%2").arg(TB_PREFIX).arg("Ied")*/;}

    /* ----------------[功能方法]--------------- */
    bool insertItem(const IedDbItem& item); // 插入
    bool updateItem(const IedDbItem& item); // 修改
protected:
    bool modifyItem(const IedDbItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,IedDbItem &item);
signals:

public slots:
};
#endif // IEDDB_H
