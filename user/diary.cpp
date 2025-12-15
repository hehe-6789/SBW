#include "diary.h"
#include "ui_diary.h"
#include <QFileDialog>
#include<QSqlQuery>
Diary::Diary(QWidget *parent, QSqlDatabase *DB, QString USERNAME)
    : QWidget(parent)
    ,db(DB)
    ,username(USERNAME)
    , ui(new Ui::Diary)
{
    ui->setupUi(this);
    this->setLayout(ui->horizontalLayout_4);//使画面跟着窗口伸缩而伸缩
    ui->date->setCalendarPopup(true);//设置选择日期的mode
    QDate currentdate=QDate::currentDate();//将默认日期设为今天
    ui->date->setDate(currentdate);
    tablename="diary";              //指定操作的表
}

Diary::~Diary()
{
    delete ui;
}


void Diary::on_pushButton_6_clicked()
{
      // qDebug()<<"what can i say";
    QSqlQuery query(*db);
    QString sqlinsert=QString("insert into %1(name,year,month,day,weather,mood,note) values(?,?,?,?,?,?,?)").arg(tablename);//处理指令
    QString weather=ui->weather->currentText().trimmed();//读取天气，心情相关数据
    QString mood=ui->mood->currentText().trimmed();
    QString note=ui->note->toPlainText().trimmed();


        QDate date=ui->date->date();                    //读取日期
        QString year=QString::number(date.year()).trimmed();
        QString month=QString::number(date.month()).trimmed();
        QString day=QString::number(date.day()).trimmed();
        //检验是否为重复提交
        QString sqlselect=QString("select * from %1 where name=? and year=? and month=? and day=?").arg(tablename);
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.addBindValue(year);
        query.addBindValue(month);
        query.addBindValue(day);
        if(!query.exec())
        {
            qDebug()<<"命令执行失败";
        }
        else{

            qDebug()<<"命令执行成功";
        }
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
            query.addBindValue(weather);
            query.addBindValue(mood);
            query.addBindValue(note);
            query.exec();                                   //执行指令
            ui->runResult->setText("提交成功");
        }

}

//删除
void Diary::on_pushButton_7_clicked()
{
    QSqlQuery query(*db);
    QString sqldelete=QString("delete from %1 where name=? and year=? and month=? and day=?").arg(tablename);
    QDate date=ui->date->date();                    //读取日期
    QString year=QString::number(date.year()).trimmed();
    QString month=QString::number(date.month()).trimmed();
    QString day=QString::number(date.day()).trimmed();
    query.prepare(sqldelete);                       //处理指令
    query.addBindValue(username);
    query.addBindValue(year);
    query.addBindValue(month);
    query.addBindValue(day);
    query.exec();
    ui->runResult->setText("删除成功");
}

//查找
void Diary::on_pushButton_8_clicked()
{
    QSqlQuery query(*db);
    QString sqlselect=QString("select * from %1 where name=? and year=? and month=? and day=?").arg(tablename);
    QDate date=ui->date->date();                    //读取日期
    QString year=QString::number(date.year()).trimmed();
    QString month=QString::number(date.month()).trimmed();
    QString day=QString::number(date.day()).trimmed();
    query.prepare(sqlselect);                       //处理指令
    query.addBindValue(username);
    query.addBindValue(year);
    query.addBindValue(month);
    query.addBindValue(day);
    query.exec();
    if(!query.next())
    {
        ui->runResult->setText("此数据不存在，请重新确定您的输入");
    }
    else
    {
        QString weather=query.value("weather").toString();
        QString mood=query.value("mood").toString();
        QString note=query.value("note").toString();
        ui->weather->setCurrentText(weather);
        ui->mood->setCurrentText(mood);
        ui->note->setText(note);
        ui->runResult->setText("已找到数据");
    }
}

//更改
void Diary::on_pushButton_9_clicked()
{
    QSqlQuery query(*db);
    QString sqlupdate=QString("update %1 set weather=?,mood=?,note=? where name=? and year=? and month=? and day=?").arg(tablename);
    QString weather=ui->weather->currentText().trimmed();//读取学习相关数据
    QString mood=ui->mood->currentText().trimmed();
    QString note=ui->note->toPlainText().trimmed();


        QDate date=ui->date->date();                    //读取日期
        QString year=QString::number(date.year()).trimmed();
        QString month=QString::number(date.month()).trimmed();
        QString day=QString::number(date.day()).trimmed();
        //检验是否为重复提交
        QString sqlselect=QString("select * from %1 where name=? and year=? and month=? and day=?").arg(tablename);
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.addBindValue(year);
        query.addBindValue(month);
        query.addBindValue(day);
        query.exec();
        if(!query.next())
        {
            qDebug()<<"您未提交过该数据，无法更改";
            ui->runResult->setText("您未提交过该数据，无法更改");
        }
        else{
            query.prepare(sqlupdate);                       //处理指令
            query.addBindValue(weather);
            query.addBindValue(mood);
            query.addBindValue(note);
            query.addBindValue(username);
            query.addBindValue(year);
            query.addBindValue(month);
            query.addBindValue(day);
            query.exec();
            ui->runResult->setText("已修改");
        }

}

//导出日记
void Diary::on_importNote_clicked()
{
    QFileDialog dialog;
    QString filepath=dialog.getSaveFileName(this,tr("save file"),"C:",tr("Text(*.txt)"));
    QFile qf(filepath);
    QTextStream io(&qf);
    if(!qf.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        qDebug()<<"open error";
    }
    else {
        QString note_read=ui->note->toPlainText();
        io<<note_read;
        ui->runResult->setText("文件已导出");
        qf.close();
    }
}

//导入日记
void Diary::on_pushButton_5_clicked()
{
    QFileDialog dialog;
    QString filepath=dialog.getOpenFileName(this,tr("import file"),"C:",tr("Text(*.txt)"));
    QFile qf(filepath);
    QTextStream io(&qf);
    if(!qf.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        qDebug()<<"open error";
    }
    else {
        ui->note->clear();
        while(!io.atEnd())
        {
            QString content=io.readLine();
            ui->note->append(content);
        }
        qf.close();
    }
}


void Diary::on_date_dateChanged(const QDate &date)
{
    ui->weather->setCurrentText("空");
    ui->mood->setCurrentText("空");
    ui->note->clear();
    ui->runResult->clear();
}

