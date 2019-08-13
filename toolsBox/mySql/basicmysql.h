#ifndef BASICMYSQL_H
#define BASICMYSQL_H

#include <QtSql>
#include <QException>
#include <QObject>
#include "toolsBox_global.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#define TB_PREFIX  "CYG"

class ProjectSql;
class SqlManager;
/* -----------------------[data]------------------------ */
class DbItem{
public:
    DbItem():id(-1){}
    bool unequal(const DbItem& item) const
    {
        return id!=item.id || name!=item.name;
    }

    int id; //id
    QString name,desc; //名字  说明
    QDateTime createTime, updateTime; //创建时间 更新时间
};
Q_DECLARE_METATYPE(DbItem)

/* -----------------------[log]------------------------ */
class  MysqlExecption:public QException
{
    QString m_msg;
    qint32  m_type;
public:
    MysqlExecption(const QString& msg,qint32 type) :m_msg(msg),m_type(type){}
    QString msg()const{return m_msg;}
    qint32  type()const{return m_type;}
};

/* -----------------------[sql]------------------------ */
class MySqlBasic : public QObject
{
    Q_OBJECT
public:
    enum{Remove,Insert,Update};
    explicit MySqlBasic(QObject *parent = 0);
    ~MySqlBasic();
    void initDb(QString fileName);

    virtual QString tableName() = 0;
    void remove(const QString &condition);
    int  maxId(const QString &idName="id", const QString &condition="");
    int  count(const QString &column_name, const QString &condition);

    QStringList  listColumn(const QString &column_name, const QString &condition);
    QVector<int> listColumnToInt(const QString &column_name, const QString &condition);
    QVector<int> selectIds(const QString &condition);

    bool updateColumn(const QString& column_name, double value, const QString &condition);
    bool updateColumn(const QString& column_name, const QString& value, const QString &condition);

signals:
    void itemChanged(int id,int type);
protected:
    bool updateTime(const QString &condition);
    void throwError(const QSqlError& err);

protected:
    QSqlDatabase *mDb;
    QString mfileName;
private:

};

//该类为sql通用类型。
template <typename T>
class BasicMySql:public MySqlBasic
{
    friend SqlManager;
    friend ProjectSql;
public:
    /* -----------------[id]------------------- */
    void removeById(int id) { //删除
        remove(QString("id = %1").arg(id));
        emit itemChanged(id,Remove);
    }
    void removeItem(const T& item) { //删除
        removeById(item.id);
    }
    QVector<T> allItems() {
        return selectItems("");
    }
    QVector<T> findItemById(int id){
        return selectItems(QString("where id = %1").arg(id));
    }

    T findById(int id){
        return findItemById(id).first();
    }
    /* -----------------[name]------------------- */
    QVector<T> findItemByName(const QString& name){
        return selectItems(QString("where name = \"%1\"").arg(name));
    }

    T findByName(const QString& name){
        return findItemByName(name).first();
    }

protected:
    virtual bool modifyItem(const T& item,const QString& cmd)=0;
    virtual void selectItem(QSqlQuery &query,T &item)=0;
    QVector<T> selectItems(const QString &condition)
    {
        QVector<T> items;
        if(mDb) {
            QSqlQuery query(*mDb);
            QString sql = QString("SELECT * from %1 %2").arg(tableName()).arg(condition);
            query.prepare(sql);            
            if(query.exec()){
                T item;
                while(query.next()){
                    selectItem(query,item);
                    items.append(item);
                }
            } else {
                qDebug()<<" "<<query.lastError().databaseText();
                qDebug()<<" "<<query.lastError().driverText();
                qDebug()<< sql;
                throwError(query.lastError());
            }
        }
        return items;
    }
};

#endif // BASICMYSQL_H
