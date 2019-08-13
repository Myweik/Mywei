#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "toolsbox.h"
#include "mySql/sqlmanager.h"
#include "basicmysql.h"

#include "dataModel/projectmodel.h"
#include "settings/cygsettings.h"
#include <QVariant>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _box = ToolsBox::getInstance();
    QString dirName = CYGSettings::getvalue("app/PrjTargetDir", "").toString();

    ProjectModel* projectModel = new ProjectModel(dirName);

//    UserDb* userDb = _box->sqlManager()->userDb();
//    qDebug() << "-----------MainWindow" << userDb->allItems().count();
//    QString fileName = "pack/PriTargetDir/CYSR.prj";
//    bool ok = _box->sqlManager()->openPro(fileName);
//    if(ok)
//    qDebug() << "-----------MainWindow" << ok << _box->sqlManager()->findPro(fileName)->substationDb()->allItems().count();


}

MainWindow::~MainWindow()
{
    delete ui;
}
