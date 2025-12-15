#ifndef DEALDATABASE_H
#define DEALDATABASE_H

#include <QSqlDatabase>

/*
--------------------
数据库模块，用于创建全局数据库访问点
--------------------
*/

class DealDatabase
{
public:
    DealDatabase();
    ~DealDatabase();
    /*
     * @brief 该函数用于获取数据库
     */
    QSqlDatabase* GetDatabase();
private:
    QSqlDatabase* DB;



};

#endif // DEALDATABASE_H
