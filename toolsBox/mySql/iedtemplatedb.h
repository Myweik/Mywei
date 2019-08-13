#ifndef IEDTEMPLATEDB_H
#define IEDTEMPLATEDB_H

#include "basicmysql.h"

class IedTemplateDbItem : public DbItem
{
public:
    IedTemplateDbItem():DbItem(){}

    QString version;        //版本
    QString manufacturer;   //制造商
    QString iedName;        //ied名称
    QString content;        //ied xml数据
    QString icdversion;     //icd版本
    QString icdcontent;     //icd xml数据
};
Q_DECLARE_METATYPE(IedTemplateDbItem)


class TOOLSBOXSHARED_EXPORT IedTemplateDb : public BasicMySql<IedTemplateDbItem>
{
    Q_OBJECT
    IedTemplateDb(QString fileName);
public:
    static IedTemplateDb *bulid(QString fileName = "");
    QString tableName(){return "iedTemplate" /*QString("%1_%2").arg(TB_PREFIX).arg("IedTemplate")*/;}

    /* ----------------[功能方法]--------------- */
    bool insertItem(const IedTemplateDbItem& item); // 插入
    bool updateItem(const IedTemplateDbItem& item); // 修改
protected:
    bool modifyItem(const IedTemplateDbItem& item,const QString& cmd);
    void selectItem(QSqlQuery &query,IedTemplateDbItem &item);
signals:

public slots:
};

#endif // IEDTEMPLATEDB_H
