#include "toolsbox.h"


#include "commonsignals.h"
#include "mySql/sqlmanager.h"
#include "thread/sqlthread.h"

ToolsBox* ToolsBox::_toolsBox = nullptr;

ToolsBox *ToolsBox::getInstance()
{
    if(_toolsBox==nullptr)
        _toolsBox= new ToolsBox();
    return _toolsBox;
}

ToolsBox::ToolsBox(QObject *parent) : QObject(parent)
{
//    qmlRegisterType<CommonSignals>("ToolsBox", 1, 0, "ToolsBox");

    set_sqlThread(new SqlThread(this));
    set_commonSignals(new CommonSignals(this));
    set_sqlManager(new SqlManager(this));
    connect(commonSignals(), SIGNAL(sendAddTask(Data_Task_TYPE, DataModelBase*)),
            sqlThread(), SLOT(onAddTask(Data_Task_TYPE, DataModelBase*)));
}
