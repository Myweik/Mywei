#include "projectmodel.h"

#include "toolsbox.h"
#include "mySql/sqlmanager.h"

ProjectModel::ProjectModel(QString projectPath, DataModelBase *parent) : _projectPath(projectPath)
{
    _parent = nullptr;
    _projectFileList = findProjectNameList(projectPath);

    SqlManager* sqlManager = ToolsBox::getInstance()->sqlManager();
    if(sqlManager && _projectFileList.count()){ //存在项目 -- 添加加载任务
        foreach(QString name, _projectFileList){
            sqlManager->openPro(name); //加载项目数据库
        }
        sendTask(Data_Task_Init);
    }
}


QStringList ProjectModel::findProjectNameList(QString projectPath)
{
    QStringList fileList;
    QDir dir(projectPath);
    if(dir.exists()){ //目录存在
        dir.setFilter(QDir::Files);
        QFileInfoList fileInfoList = dir.entryInfoList();
        for(int inf = 0; inf < fileInfoList .count(); inf ++)
        {
            QString fileName = fileInfoList.at(inf).fileName();
            if(fileName.right(4) == ".prj")
                fileList << projectPath + "/" + fileName;
        }
    }
    return fileList;
}

//-------------------------------------------
void ProjectModel::initTask()
{
    qDebug() << "------------------------ProjectModel::initTask()" << _projectFileList;
}

void ProjectModel::addTask()
{

}

void ProjectModel::updataTask()
{

}

void ProjectModel::removeTask()
{

}
