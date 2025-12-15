#include "mainwindow.h"
#include "maininterface.h"
#include "ui_mainwindow.h"
#include "user/studyrecord.h"
#include <QDir>
#include <manager/manager.h>
MainWindow::MainWindow(QWidget *parent,QSqlDatabase* DB)
    : QMainWindow(parent)
    , db(DB)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());//禁止窗口伸缩
    //this->setLayout(ui->verticalLayout);
#if 0
    QSqlQuery query(*db);
    if(!db->open())
    {
         qDebug()<<"open error";
    }
    else{
        QString sqlcreate=QString("create table login(name text primary key,password text)");//建立表，建立过一次后忽略
        query.exec(sqlcreate);
    }
#endif
    QPixmap octoback(":/picture/octoback.png");//设置图片
    octo=QPixmap(":/picture/octoplus.png");//设置图片
    qDebug() << "当前工作目录：" << QDir::currentPath();//打印工作路径
    if (octo.isNull()) {
        qDebug() << "图片加载失败！请检查路径";
        return;
    }
    //QSize size=ui->octo->size();
    //qDebug()<<size;
    //ui->octo->setPixmap(octo.scaled(247,369));           //为标签设置图片
    //ui->octoback->setPixmap(octoback.scaled(247,369));

    tablename=QString("login");//设置操作表
    ui->pushButton->setShortcut(QKeySequence(Qt::Key_Return));

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*----
登录实现
----*/
void MainWindow::on_pushButton_clicked()
{

    QSqlQuery query(*db);

        QString name=ui->yongHuMing->text().trimmed();  //读取输入
        QString password=ui->miMa->text().trimmed();
        QString pass=QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Md5).toHex();
        QString sqlselect1=QString("select * from %1 where name=?").arg(tablename);//检测用户名
        QString sqlselect2=QString("select * from %1 where name=? and password=?").arg(tablename);//检测用户名和密码

        query.prepare(sqlselect1);                      //预编译
        query.addBindValue(name);                       //绑定参数
        query.exec();
        if(!query.next())
        {
            ui->messageShow->setText("用户名不存在");

        }
        else
        {
            query.prepare(sqlselect2);
            query.addBindValue(name);
            if(tablename=="login")
            query.addBindValue(password);
            else if(tablename=="manager")
                query.addBindValue(pass);
            query.exec();
            if(!query.next())
            {
                ui->messageShow->setText("用户名或密码错误");
            }
            else
            {
                ui->messageShow->setText("登录成功，请稍等");
                username=query.value("name").toString();
                qDebug()<<username;
                this->hide();
                if(tablename=="login")
                {
                    this->releaseKeyboard();
                MainInterface* s=new MainInterface(nullptr,db,username);
                s->show();
                }
                if(tablename=="manager")
                {
                    Manager*m=new Manager(nullptr,db);
                    m->show();
                }
            }

    }




}

/*----
注册实现
----*/
void MainWindow::on_pushButton_2_clicked()
{
    if(tablename=="login")
    {
    QSqlQuery query(*db);
    QString name=ui->yongHuMing->text().trimmed();
    QString password=ui->miMa->text().trimmed();
    if(name==""||password=="")
    {
        ui->messageShow->setText("请勿使用空的用户名或密码");
    }
    else{
    QString sqlselect=QString("select * from %1 where name=? ").arg(tablename);//检测用户名和密码
    query.prepare(sqlselect);//构建指令
    query.addBindValue(name);
    query.exec();//执行指令
     if(query.next())
         ui->messageShow->setText("用户名已存在，请更换。");
     else{
         QString sqlinsert =QString("insert into %1 values(?,?)").arg(tablename) ;//构建指令
         query.prepare(sqlinsert);
         query.addBindValue(name);

         query.addBindValue(password);
         query.exec();//执行指令
         ui->messageShow->setText("注册成功");
     }
    }

    }
    else if(tablename=="manager")
    {
        ui->messageShow->setText("管理员账户不可注册");
    }

    // QString sqlselect=QString("select * from %1 where name=? and password=?").arg(tablename);//检测用户名和密码
    // query.prepare(sqlselect);//构建指令
    // query.addBindValue(name);
    // query.addBindValue(password);
    // query.exec();//执行指令
    // if(query.next())
    //     ui->messageShow->setText("注册成功");
    // else{
    //     ui->messageShow->setText("注册失败");
    // }
    }




    void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
    {
        if(ui->comboBox->currentText()=="user")
            tablename="login";
        else if(ui->comboBox->currentText()=="manager")
            tablename="manager";


    }

