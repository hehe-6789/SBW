#include "englishrecord.h"
#include "ui_englishrecord.h"
#include<QSqlQuery>
EnglishRecord::EnglishRecord(QWidget *parent,QSqlDatabase*DB,QString USERNAME)
    : QWidget(parent)
    ,db(DB)
    ,username(USERNAME)
    , ui(new Ui::EnglishRecord)
{
    ui->setupUi(this);
    this->setLayout(ui->horizontalLayout_4);
    QDate date;
    ui->dateEdit->setDate(date.currentDate());
    ui->dateEdit_2->setDate(date.currentDate());
    tablename="course";
}

EnglishRecord::~EnglishRecord()
{
    delete ui;
}
//提交
void EnglishRecord::on_pushButton_3_clicked()
{
    QSqlQuery query(*db);
    QString sqlinsert=QString("insert into %1(name,year,month,day,course,endyear,endmonth,endday,remain) values(?,?,?,?,?,?,?,?,?)").arg(tablename);//处理指令
    QString course=ui->course->text().trimmed();//读取事项相关数据


    QDate date=ui->dateEdit->date();                    //读取开始日期
    QString year=QString::number(date.year()).trimmed();
    QString month=QString::number(date.month()).trimmed();
    QString day=QString::number(date.day()).trimmed();
    QDate A(date.year(),date.month(),date.day());                                        //存储开始日期
    date=ui->dateEdit_2->date();                    //读取结束日期
    QString endyear=QString::number(date.year()).trimmed();
    QString endmonth=QString::number(date.month()).trimmed();
    QString endday=QString::number(date.day()).trimmed();
    QDate B(date.year(),date.month(),date.day());    //存储结束日期
    int C= A.daysTo(B);                                        //存储日期差值;
    qDebug()<<C;
    if(course=="")
    {
        ui->runResult->setText("请不要提交空的学习量或空的学习时间");
    }
    else if(C<0)
    {
        ui->runResult->setText("你无法穿越时间");
    }
    else{


        //检验是否为重复提交
        QString sqlselect=QString("select * from %1 where name=? and course=?").arg(tablename);
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.addBindValue(course);
        query.exec();
        if(query.next())
        {
            qDebug()<<"您已提交，请不要重复提交";
            ui->runResult->setText("您已提交，请不要重复提交");
        }
        else{
            query.prepare(sqlinsert);
            query.addBindValue(username);                       //绑定数据
            query.addBindValue(year);
            query.addBindValue(month);
            query.addBindValue(day);
            query.addBindValue(course);
            query.addBindValue(endyear);
            query.addBindValue(endmonth);
            query.addBindValue(endday);
            query.addBindValue(C);
            query.exec();                                   //执行指令
            ui->runResult->setText("提交成功");
        }
    }
}

//删除
void EnglishRecord::on_pushButton_4_clicked()
{
    QSqlQuery query(*db);
    QString sqldelete=QString("delete from %1 where name=? and course=?").arg(tablename);
    QString course=ui->course->text();
    query.prepare(sqldelete);                       //处理指令
    query.addBindValue(username);
    query.addBindValue(course);
    query.exec();
    ui->runResult->setText("删除成功");
}

//修改
void EnglishRecord::on_pushButton_2_clicked()
{
    QSqlQuery query(*db);
    QString sqlupdate=QString("update %1 set year=?,month=?,day=?,endyear=?,endmonth=?,endday=?,remain=? where name=? and course=?").arg(tablename);
    QString course=ui->course->text();
    if(course=="")
    {
        ui->runResult->setText("请不要提交空的学习量或空的学习时间");
    }
    else{

        //检验是否提交过
        QString sqlselect=QString("select * from %1 where name=? and course=?").arg(tablename);
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.addBindValue(course);
        query.exec();
        if(!query.next())
        {
            qDebug()<<"您未提交过该数据，无法更改";
            ui->runResult->setText("您未提交过该数据，无法更改");
        }
        else{
            query.prepare(sqlupdate);                       //处理指令
            //获取日期
            QDate date=ui->dateEdit->date();                    //读取日期
            QString year=QString::number(date.year()).trimmed();
            QString month=QString::number(date.month()).trimmed();
            QString day=QString::number(date.day()).trimmed();
            QDate date2=ui->dateEdit_2->date();
            QString endyear=QString::number(date2.year()).trimmed();
            QString endmonth=QString::number(date2.month()).trimmed();
            QString endday=QString::number(date2.day()).trimmed();
            query.addBindValue(year);
            query.addBindValue(month);
            query.addBindValue(day);
            query.addBindValue(endyear);
            query.addBindValue(endmonth);
            query.addBindValue(endday);
            query.addBindValue(date.daysTo(date2));
            query.addBindValue(username);
            query.addBindValue(course);

            if(!query.exec())
            {
                qDebug()<<"运行失败";
            }

            else{ui->runResult->setText("已修改");}
        }
    }
}

//查找
void EnglishRecord::on_pushButton_clicked()
{
    QSqlQuery query(*db);
    QString sqlselect=QString("select * from %1 where name=? and course=?").arg(tablename);

    QString course=ui->course->text();
    query.prepare(sqlselect);                       //处理指令
    query.addBindValue(username);
    query.addBindValue(course);
    query.exec();
    if(!query.next())
    {
        ui->runResult->setText("此数据不存在，请重新确定您的输入");
    }
    else
    {
        QSqlQuery query(*db);
        QString sqlselect=QString("select * from %1 where name=? and course=?").arg(tablename);
        query.prepare(sqlselect);                       //处理指令
        query.addBindValue(username);
        query.addBindValue(course);
        query.exec();
        if(!query.next())
        {
            ui->runResult->setText("此数据不存在，请重新确定您的输入");
        }
        else
        {
            int year=query.value("year").toInt();
            int month=query.value("month").toInt();
            int day=query.value("day").toInt();
            int endyear=query.value("endyear").toInt();
            int endmonth=query.value("endmonth").toInt();
            int endday=query.value("endday").toInt();
            QDate date(year,month,day);
            QDate date2(endyear,endmonth,endday);
            ui->dateEdit->setDate(date);
            ui->dateEdit_2->setDate(date2);
            ui->runResult->setText("已找到数据");
        }
    }
}

//更新剩余时间
void EnglishRecord::on_pushButton_5_clicked()
{
    QDate date;
    QDate date2;
    QSqlQuery query(*db);
    QSqlQuery query2(*db);
    QString sqlselect=QString("select * from %1 where name=? ").arg(tablename);
    QString sqlupdate=QString("update %1 set remain=? where name=? and course=?").arg(tablename);
    query.prepare(sqlselect);                       //处理指令
    query.addBindValue(username);
    if(!query.exec())
    {
        qDebug()<<"命令发送失败";
    }
    else
    {
        while(query.next())
        {
            int endyear=query.value("endyear").toInt(); //获取结束时间
            int endmonth=query.value("endmonth").toInt();
            int endday=query.value("endday").toInt();
            date2=QDate(endyear,endmonth,endday);
            int remain=date.currentDate().daysTo(date2);  //计算与当前时间差值
            query2.prepare(sqlupdate);
            query2.addBindValue(remain);
            query2.addBindValue(query.value("name").toString());
            query2.addBindValue(query.value("course").toString());
            query2.exec();                                  //执行
        }
    }

}

