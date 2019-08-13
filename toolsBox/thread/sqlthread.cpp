#include "sqlthread.h"
#include "AVThread.h"

SqlThread::SqlThread(QObject *parent) : QObject(parent)
{

}

SqlThread::~SqlThread()
{
    _sqlThread.clearAllTask();
    _sqlThread.stop();
}

void SqlThread::onAddTask(Data_Task_TYPE type, DataModelBase *data)
{
    onAddTask(new DataModelTask(type, data));
}

void SqlThread::onAddTask(DataModelTask *task)
{
    _sqlThread.addTask(task);
}
