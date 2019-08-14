#include "datamodelbase.h"
#include "toolsbox.h"
#include "commonsignals.h"

/* ------------------------------------[DataModelBase]--------------------------------------- */
DataModelBase::DataModelBase(QObject *parent)
    : QObject(parent)
    , _parent(nullptr)
    , _projectName("")
{

}

DataModelBase *DataModelBase::getParent()
{
    return _parent;
}

QStringList DataModelBase::getChildNameList()
{
    return _childMap.keys();
}

bool DataModelBase::contains(QString name)
{
    return !name.isEmpty() && _childMap.keys().contains(name);
}

bool DataModelBase::contains(DataModelBase *base)
{
    if(!base)
        return false;
    foreach(DataModelBase* item, _childMap){
        if(item == base)
            return true;
    }
    return false;
}

bool DataModelBase::addChild(QString name, DataModelBase *base)
{
    if(!contains(name) && base){
        _childMap[name] = base;
        return true;
    }
    return false;
}

bool DataModelBase::removeChild(QString name)
{
    if(!contains(name) && !name.isEmpty()){
        delete _childMap[name];
        _childMap.remove(name);
        return true;
    }
    return false;
}

void DataModelBase::sendTask(Data_Task_TYPE Type)
{
    emit ToolsBox::getInstance()->commonSignals()->sendAddTask(Type, this);
}

/* ------------------------------------[DataBaseModel]--------------------------------------- */

/* ------------------------------------[DataModelTask]--------------------------------------- */

DataModelTask::DataModelTask(Data_Task_TYPE type, DataModelBase *object)
    : _object(object)
{
    _type = type;
}

void DataModelTask::run()
{
    if(_object){
        switch ((Data_Task_TYPE)_type) {
        case Data_Task_Init:
            _object->initTask();
            break;
        case Data_Task_Add:
            _object->addTask();
            break;
        case Data_Task_Updata:
            _object->updataTask();
            break;
        case Data_Task_Remove:
            _object->removeTask();
            break;
        }
    }
}



