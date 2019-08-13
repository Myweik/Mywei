#include "mainwindow.h"
#include <QApplication>

#include "toolsbox.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToolsBox* box = ToolsBox::getInstance();

    MainWindow w;
    w.show();


    int rtn = a.exec();
    delete box;
    return rtn;
}
