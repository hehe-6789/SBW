#include "billrecord.h"
#include "ui_billrecord.h"
#include<QSqlQuery>
BillRecord::BillRecord(QWidget *parent, QSqlDatabase *DB, QString USERNAME)
    : QMainWindow(parent)
    , db(DB)
    , username(USERNAME)
    , ui(new Ui::BillRecord)
{
    ui->setupUi(this);
    this->setLayout(ui->horizontalLayout_2);
    tablename="bill";
    QDate date;
    ui->date->setDate(date.currentDate());
    validator = new QDoubleValidator(-999999999999.0, 0.0, 2, this);//限制金额的输入//支出
    validator2 = new QDoubleValidator(0.0,999999999999.0, 2, this);//限制金额的输入//收入

    validator->setNotation(QDoubleValidator::StandardNotation); // 标准小数格式
    ui->moneyNum->setValidator(validator);


}

BillRecord::~BillRecord()
{
    delete ui;
}



//提交
void BillRecord::on_pushButton_5_clicked()
{
    QSqlQuery query(*db);
    QString sqlinsert=QString("insert into %1(name,year,month,day,amount,category,method,note) values(?,?,?,?,?,?,?,?)").arg(tablename);//处理指令
    QString moneynum=ui->moneyNum->text().trimmed();//读取bill相关数据
    QString note=ui->note->toPlainText().trimmed();
    QString type=ui->type->currentText().trimmed();
    QString method=ui->method->currentText().trimmed();

    if(moneynum=="")
    {
        ui->runResult->setText("请不要提交空金额");
    }
    else{
        QDate date=ui->date->date();                    //读取日期
        QString year=QString::number(date.year()).trimmed();
        QString month=QString::number(date.month()).trimmed();
        QString day=QString::number(date.day()).trimmed();

            query.prepare(sqlinsert);
            query.addBindValue(username);                       //绑定数据
            query.addBindValue(year);
            query.addBindValue(month);
            query.addBindValue(day);
            query.addBindValue(moneynum);
            query.addBindValue(type);
            query.addBindValue(method);
            query.addBindValue(note);
            query.exec();                                   //执行指令
            ui->runResult->setText("提交成功");
    }
}

//删除
void BillRecord::on_pushButton_4_clicked()
{
    QSqlQuery query(*db);
    QString sqldelete=QString("delete from %1 where name=? and id=?").arg(tablename);
    QString id=ui->id->text();
    query.prepare(sqldelete);                       //处理指令
    query.addBindValue(username);
    query.addBindValue(id);
    query.exec();
    ui->runResult->setText("删除成功");
}

//查找
void BillRecord::on_pushButton_3_clicked()
{
    QSqlQuery query(*db);
    QString sqlselect=QString("select * from %1 where name=? and id=?").arg(tablename);
    QString id=ui->id->text();
    query.prepare(sqlselect);                       //处理指令
    query.addBindValue(username);
    query.addBindValue(id);
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
        ui->date->setDate(QDate(year,month,day));
        ui->moneyNum->setText(query.value("amount").toString());
        ui->type->setCurrentText(query.value("category").toString());
        ui->method->setCurrentText(query.value("method").toString());
        ui->note->setText(query.value("note").toString());
        ui->runResult->setText("已找到数据");
    }

}

//更改
void BillRecord::on_pushButton_2_clicked()
{
    QSqlQuery query(*db);
    QString sqlupdate=QString("update %1 set year=?,month=?,day=?,amount=?,category=?,method=?,note=? where name=? and id=?").arg(tablename);
    QString id=ui->id->text();
    QString moneynum=ui->moneyNum->text();
    QString type=ui->type->currentText();
    QString method=ui->method->currentText();
    QString note=ui->note->toPlainText();

    if(moneynum=="")
    {
        ui->runResult->setText("请不要提交空的学习量或空的学习时间");
    }
    else{
        QDate date=ui->date->date();                    //读取日期
        QString year=QString::number(date.year()).trimmed();
        QString month=QString::number(date.month()).trimmed();
        QString day=QString::number(date.day()).trimmed();
        //检验是否存在数据
        QString sqlselect=QString("select * from %1 where name=? and id=?").arg(tablename);
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.addBindValue(id);
        query.exec();
        if(!query.next())
        {
            qDebug()<<"您未提交过该数据，无法更改";
            ui->runResult->setText("您未提交过该数据，无法更改");
        }
        else{
            query.prepare(sqlupdate);                       //处理指令
            query.addBindValue(year);
            query.addBindValue(month);
            query.addBindValue(day);
            query.addBindValue(moneynum);
            query.addBindValue(type);
            query.addBindValue(method);
            query.addBindValue(note);
            query.addBindValue(username);
            query.addBindValue(id);
            query.exec();
            ui->runResult->setText("已修改");
        }
    }
}


void BillRecord::on_type_currentTextChanged(const QString &arg1)
{
    QString type=ui->type->currentText();
    if(type=="收入")
    {
       ui->moneyNum->setValidator(validator2);
    }
    else if(type=="支出")
    {
        ui->moneyNum->setValidator(validator);
    }
}

