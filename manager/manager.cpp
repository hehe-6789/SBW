#include "manager.h"
#include "ui_manager.h"
#include <QSqlQuery>
#include<QCryptographicHash>
Manager::Manager(QWidget *parent,QSqlDatabase* DB)
    : QWidget(parent)
    ,db(DB)
    , ui(new Ui::Manager)
{
    ui->setupUi(this);
    this->setLayout(ui->horizontalLayout);
    tablename="login";
    model=new QSqlQueryModel;
    tablenamelist=new QList<QString>;
    tablenamelist->append("login");
    tablenamelist->append("study");
    tablenamelist->append("diary");
    tablenamelist->append("bill");
    tablenamelist->append("course");

}

Manager::~Manager()
{
    delete ui;
    delete tablenamelist;
    delete model;
}
//删除实现
void Manager::on_pushButton_clicked()
{
    QSqlQuery query(*db);
     QString username=ui->username->text();
    for(const auto i:*tablenamelist)
    {
        QString sqldelete=QString("delete from %1 where name=?").arg(i);
        query.prepare(sqldelete);
        query.addBindValue(username);
        query.exec();
        ui->runResult->setText("已删除");
    }

}

//查找实现
void Manager::on_pushButton_2_clicked()
{
    model->clear();
    QSqlQuery query(*db);
    QString sqlselect=QString("select * from %1 where name=?").arg(tablename);
    query.prepare(sqlselect);
    QString username=ui->username->text();
    query.addBindValue(username);
    if(!query.exec())
    {
        qDebug()<<"运行失败";
    }
    else{
        model->setQuery(query);
        model->setHeaderData(0,Qt::Horizontal,"username");
        model->setHeaderData(0,Qt::Horizontal,"password");
        ui->tableView->setModel(model);
        ui->runResult->setText("已找到");
    }
}

//修改密码实现
void Manager::on_pushButton_3_clicked()
{
    QSqlQuery query(*db);
    QString sqlupdate=QString("update %1 set password=?" ).arg("manager");
    query.prepare(sqlupdate);
    QString password=ui->password->text();
    QString pass=QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Md5).toHex();
    query.addBindValue(pass);
    query.exec();
    ui->runResult->setText("已修改");
}

//刷新实现
void Manager::on_pushButton_4_clicked()
{
    model->clear();
    QSqlQuery query(*db);
    QString selectsql=QString("select * from %1").arg(tablename);
    query.exec(selectsql);
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,"username");
    model->setHeaderData(0,Qt::Horizontal,"password");
    ui->tableView->setModel(model);
    ui->runResult->setText("已刷新");
}

