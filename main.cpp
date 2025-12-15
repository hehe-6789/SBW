#include "dealdatabase.h"
#include "maininterface.h"
#include "mainwindow.h"

#include <QApplication>

#include <manager/manager.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    DealDatabase db;
    //主程序
    MainWindow* w=new MainWindow(nullptr,db.GetDatabase());
    w->show();
    //测试主界面
    //MainInterface* window=new MainInterface(nullptr,db.GetDatabase(),"尘");
    //window->show();
    //测试管理员界面
    //Manager*manager=new Manager(nullptr,db.GetDatabase());
    //manager->show();
    //测试数据分析界面
    // dataAnalyse* analyse=new dataAnalyse(nullptr,db.GetDatabase(),"尘");
    // analyse->show();
    //测试bill界面
    // BillRecord* b=new BillRecord(nullptr,db.GetDatabase(),"尘");
    // b->show();
    //测试diary界面
    //Diary *d=new Diary(nullptr,db.GetDatabase(),"尘");
    //d->show();

    return a.exec();
}
