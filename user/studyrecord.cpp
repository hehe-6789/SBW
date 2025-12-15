#include "studyrecord.h"
#include "ui_studyrecord.h"

#include <QFileDialog>

StudyRecord::StudyRecord(QWidget *parent,QSqlDatabase* DB,QString USERNAME)
    : QWidget(parent)
    , db(DB)
    ,username(USERNAME.trimmed())
    , ui(new Ui::StudyRecord)
{
    ui->setupUi(this);
    this->setLayout(ui->horizontalLayout_2);//使画面跟着窗口伸缩而伸缩
    ui->date->setCalendarPopup(true);//设置选择日期的mode
    QDate currentdate=QDate::currentDate();//将默认日期设为今天
    ui->date->setDate(currentdate);
    QDoubleValidator *validator = new QDoubleValidator(0.0, 1440.0, 2, this);//限制学习量与学习时间的输入
    validator->setNotation(QDoubleValidator::StandardNotation); // 标准小数格式
    ui->studyTime->setValidator(validator);
    ui->studyNum->setValidator(validator);
    tablename="study";              //指定操作的表
    // qDebug()<< ui->date->text();


}

StudyRecord::~StudyRecord()
{
    delete ui;
}
// 提交实现
void StudyRecord::on_pushButton_clicked()
{

    QSqlQuery query(*db);
    QString sqlinsert=QString("insert into %1(name,year,month,day,studynum,studytime,studynote) values(?,?,?,?,?,?,?)").arg(tablename);//处理指令
    QString studynum=ui->studyNum->text().trimmed();//读取学习相关数据
    QString studytime=ui->studyTime->text().trimmed();
    QString studynote=ui->studyNote->toPlainText().trimmed();
    if(studynum==""||studytime=="")
    {
        ui->runResult->setText("请不要提交空的学习量或空的学习时间");
    }
    else if(studynum=="0"&&studytime=="0")
    {
        ui->runResult->setText("孩子，你不是神，不能凭空制造时间");
    }
    else{
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
    query.addBindValue(studynum);
    query.addBindValue(studytime);
    query.addBindValue(studynote);
    query.exec();                                   //执行指令
    ui->runResult->setText("提交成功");
    }
    }
}


//删除实现
void StudyRecord::on_pushButton_2_clicked()
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

//查找实现
void StudyRecord::on_pushButton_3_clicked()
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
    QString studynum=query.value("studynum").toString();
    QString studytime=query.value("studytime").toString();
    QString studynote=query.value("studynote").toString();
    ui->studyNum->setText(studynum);
    ui->studyTime->setText(studytime);
    ui->studyNote->setText(studynote);
    ui->runResult->setText("已找到数据");
    }


}
//更改实现
void StudyRecord::on_pushButton_4_clicked()
{
    QSqlQuery query(*db);
    QString sqlupdate=QString("update %1 set studynum=?,studytime=?,studynote=? where name=? and year=? and month=? and day=?").arg(tablename);
    QString studynum=ui->studyNum->text().trimmed();//读取学习相关数据
    QString studytime=ui->studyTime->text().trimmed();
    QString studynote=ui->studyNote->toPlainText().trimmed();
    if(studynum==""||studytime=="")
    {
        ui->runResult->setText("请不要提交空的学习量或空的学习时间");
    }
    else{
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
    query.addBindValue(studynum);
    query.addBindValue(studytime);
    query.addBindValue(studynote);
    query.addBindValue(username);
    query.addBindValue(year);
    query.addBindValue(month);
    query.addBindValue(day);
    query.exec();
    ui->runResult->setText("已修改");
    }
    }
}


//导出文件实现
void StudyRecord::on_importNote_clicked()
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
        QString note_read=ui->studyNote->toPlainText();
        io<<note_read;
        ui->runResult->setText("文件已导出");
        qf.close();
    }

}
//导入文件实现

void StudyRecord::on_pushButton_5_clicked()
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
        ui->studyNote->clear();
        while(!io.atEnd())
        {
            QString content=io.readLine();
            ui->studyNote->append(content);
        }
        qf.close();
    }
}

//修改日期时清空控件内容
void StudyRecord::on_date_dateChanged(const QDate &date)
{
    ui->studyNum->clear();
    ui->studyTime->clear();
    ui->studyNote->clear();
    ui->runResult->clear();
}

