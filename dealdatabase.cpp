#include "dealdatabase.h"


/*
 * @brief 构造函数，初始化全局数据库接入点
 */
DealDatabase::DealDatabase()
{
    DB=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));//初始化db
    DB->setDatabaseName("SBW.db");//操作SBW
    if(!DB->open())//打开
    {
        qDebug()<<"open error";
    }
    else
    {
        qDebug()<<"open success";
    }
}
/*
 *@brief 析构函数
 */

DealDatabase::~DealDatabase()
{
    DB->close();
    delete DB;
}
/*
 * @return 返回全局数据库接入点
 */

QSqlDatabase *DealDatabase::GetDatabase()
{
    return DB;
}
