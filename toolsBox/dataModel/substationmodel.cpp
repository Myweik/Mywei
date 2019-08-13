#include "substationmodel.h"

SubstationModel::SubstationModel(SubstationDbItem data, DataModelBase *parent)
{
    _data = data;
    _parent = parent;
    if(parent && dynamic_cast<DataBaseModel *>(parent))
        dynamic_cast<DataBaseModel *>(parent)->addChild(this);
}

void SubstationModel::initTask()
{

}

void SubstationModel::addTask()
{

}

void SubstationModel::updataTask()
{

}

void SubstationModel::removeTask()
{

}
