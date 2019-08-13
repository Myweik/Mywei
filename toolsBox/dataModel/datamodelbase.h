#ifndef DATAMODELBASE_H
#define DATAMODELBASE_H

#include <QObject>
#include <QMap>
#include "../thread/AVThread.h"
#include "toolsBox_global.h"
//TOOLSBOXSHARED_EXPORT

enum Data_Task_TYPE
{
     Data_Task_Init = 0  //初始化
    ,Data_Task_Add       //添加到数据库
    ,Data_Task_Updata    //同步到数据库
    ,Data_Task_Remove    //删除到数据库 -- 同时释放dataModel
};

/* ----------------------------[DataModelBase]-------------------------------------- */
class DataModelBase : public QObject
{
    Q_OBJECT
public:
    typedef enum MOUNT_TYPE
    {
        /* 项目根 */
          MOUNT_PROJRCT = 0x0000
        /* 数据 */
        , MOUNT_SUBSTATION  //变电站
        , MOUNT_VOL_LEVEL   //电压级
        , MOUNT_BAY         //设备组间隔
        , MOUNT_IED         //装置
        , MOUNT_AP          //访问点
        , MOUNT_LD          //逻辑设备
        , MOUNT_LN          //逻辑节点
        , MOUNT_LN_DATA     //数据项
        /* 图元数据 */
        , MOUNT_VIEW_ITEM = 0x0101 //基本图元
    } MOUNT_TYPE;
    explicit DataModelBase(QObject *parent = nullptr);

    /* 递归关系 */
    DataModelBase* getParent();
    QStringList    getChildNameList();
    bool           contains(QString name);
    bool           contains(DataModelBase* base);
    bool           addChild(QString name, DataModelBase* base);
    bool           removeChild(QString name);

    void           sendTask(Data_Task_TYPE Type);
    /* 子类可复用的方法 */
    virtual void initTask()=0;
    virtual void addTask()=0;
    virtual void updataTask()=0;
    virtual void removeTask()=0;
    virtual MOUNT_TYPE type()=0;
signals:

public slots:

protected:
    DataModelBase* _parent;
    QMap<QString, DataModelBase*> _childMap;
};
/* ----------------------------[DataBaseModel]-------------------------------------- */

template <typename T>
class DataBaseModel:public DataModelBase
{
public:
    /* 递归关系 */
    bool addChild(DataBaseModel* base){
        if(base)
         return DataModelBase::addChild(base->getData().name, base);
        return false;
    }

    bool removeChild(DataBaseModel* base){
        if(base && !contains(base) && !base->getData().name.isEmpty()){
            return DataModelBase::removeChild(base->getData().name);
        }
        return false;
    }

    T getData() { return _data;}
protected:
    T _data;    //数据
};

/* ----------------------------[DataModelTask]-------------------------------------- */

class DataModelTask : public Task
{
public:
    explicit DataModelTask(Data_Task_TYPE type,  DataModelBase* data);

    void run();
signals:

public slots:

private:
    DataModelBase *_data;
};

#endif // DATAMODELBASE_H
