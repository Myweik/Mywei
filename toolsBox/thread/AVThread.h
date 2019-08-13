#ifndef AVTHREAD_H
#define AVTHREAD_H

#include <QThread>
#include <QMutex>
#include <list>

using namespace std;

class Task{
public :
    virtual ~Task(){}
    virtual void run()=0;
protected:
    int _type;
};

class AVThread : public QThread
{
public:
    AVThread();
    ~AVThread();
    void addTask(Task *task);
    void stop();
    void clearAllTask();
    int size();
protected :
    virtual void run();
private :
    Task* getTask();
private :
    list<Task *> mFuns;
    QMutex mMutex;
    bool mIsRunning;
};
#endif // AVTHREAD_H
