#ifndef SQLTHREAD_H
#define SQLTHREAD_H

#include <QObject>
#include "dataModel/datamodelbase.h"

class AVThread;

class TOOLSBOXSHARED_EXPORT SqlThread : public QObject
{
    Q_OBJECT
public:
    SqlThread(QObject *parent = nullptr);
    ~SqlThread();

signals:

public slots:
    void onAddTask(Data_Task_TYPE type ,DataModelBase* data);
    void onAddTask(DataModelTask* task);
private:
    AVThread _sqlThread;
};

#endif // SQLTHREAD_H
