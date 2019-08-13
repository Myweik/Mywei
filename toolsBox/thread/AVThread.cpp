#include "AVThread.h"
#include <Windows.h>
AVThread::AVThread()
    : mIsRunning(false)
{
    start();
}

AVThread::~AVThread()
{
    stop();
    quit();
    wait(100);
    if(mIsRunning){
        terminate();//强行终断
    }

    mMutex.lock();
    list<Task *>::iterator begin = mFuns.begin();
    list<Task *>::iterator end = mFuns.end();
    while(begin != end){
        Task *task = *begin;
        if(task != nullptr)
            delete task;
        ++begin;
    }
    mFuns.clear();
    mMutex.unlock();
}

void AVThread::stop(){
    mIsRunning = false;
}

void AVThread::clearAllTask(){
    mMutex.lock();
    list<Task *>::iterator begin = mFuns.begin();
    list<Task *>::iterator end = mFuns.end();
    while(begin != end){
        Task *task = *begin;
        if(task != nullptr)
            delete task;
        task = nullptr;
        begin = mFuns.erase(begin);
    }
    mFuns.clear();
    mMutex.unlock();
}

int AVThread::size(){
    mMutex.lock();
    int size = mFuns.size();
    mMutex.unlock();
    return size;
}

void AVThread::addTask(Task *task)
{
    mMutex.lock();
    mFuns.push_back(task);
    mMutex.unlock();

    if(!mIsRunning)
        start();
}

Task *AVThread::getTask(){
    mMutex.lock();
    Task *task = nullptr;
    if(mFuns.size() > 0){
        task = mFuns.front();
        mFuns.pop_front();
    }
    mMutex.unlock();
    return task;
}

void AVThread::run(){
    mIsRunning = true;
//    SYSTEM_INFO info;
//    GetSystemInfo(&info);
//    if(info.dwNumberOfProcessors == 4)
//        SetThreadAffinityMask(currentThread(), 0x08);

    while(mIsRunning){
        Task * task = getTask();
        if(task == nullptr){

        }else{
            task->run();
            delete task;
        }
        QThread::usleep(10);
    }
}
