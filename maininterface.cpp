#include "maininterface.h"
#include "ui_maininterface.h"

#include <QToolBar>

MainInterface::MainInterface(QWidget *parent,QSqlDatabase *DB,QString USERNAME)
    : QMainWindow(parent)
    ,db(DB)
    ,username(USERNAME)
    , ui(new Ui::MainInterface)
{
    ui->setupUi(this);
    initInterface();
}

MainInterface::~MainInterface()
{
    delete ui;
}

void MainInterface::initInterface()
{
    windows=new QStackedWidget(this);                               //初始化堆叠窗口
    windows->setVisible(false);
    this->setCentralWidget(windows);                                //将mainwindow中centralwindow设置为windows
    studyRecord =new StudyRecord(this,db,username);
    diary=new Diary(this,db,username);
    //studyRecord->resize(ui->centralwidget->size());此方法无效
    billRecord=new BillRecord(this,db,username);
    englishRecord=new EnglishRecord(this,db,username);
    dataanalyse=new dataAnalyse(this,db,username);
    QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Expanding); //适应centralwidget窗口布局的sizepolicy
    studyRecord->setSizePolicy(sp);                                 //设置sizepolicy
    billRecord->setSizePolicy(sp);
    englishRecord->setSizePolicy(sp);
    dataanalyse->setSizePolicy(sp);
    windows->addWidget(studyRecord);                                //添加堆叠窗口
    windows->addWidget(diary);
    windows->addWidget(billRecord);
    windows->addWidget(englishRecord);
    windows->addWidget(dataanalyse);
    windows->setCurrentIndex(0);                                    //设置最开始窗口
    windows->setVisible(true);
    qDebug()<<windows->size();

}
//study跳转实现
void MainInterface::on_actionstudy_triggered()
{
    qDebug()<<"点击";
    windows->setCurrentIndex(0);
}

//diary跳转实现
void MainInterface::on_actiondiary_triggered()
{
    windows->setCurrentIndex(1);


}
//bill跳转实现                               //在删除note时出现了意外，改动了不该改动的文件，导致从note开始槽函数向前移动了一个
void MainInterface::on_actionbill_triggered()
{
    windows->setCurrentIndex(2);
}


//bill跳转实现
void MainInterface::on_actionEnglish_triggered()
{
    windows->setCurrentIndex(3);
}

//English跳转实现
void MainInterface::on_actiondataanalyze_triggered()
{
    windows->setCurrentIndex(4);

}


void MainInterface::on_actionocto_triggered()
{

    qDebug()<<"octo";
}

void MainInterface::keyPressEvent(QKeyEvent *event) //键盘按下事件
{
     int index=windows->currentIndex();
    switch (event->key()) {
    case Qt::Key_Left:
        qDebug()<<"Left";
        if(windows->currentIndex()!=0)
         windows->setCurrentIndex(index-1);
        else if(windows->currentIndex()==0)
            windows->setCurrentIndex(4);
        break;
    case Qt::Key_Right:
        if(windows->currentIndex()!=4)
            windows->setCurrentIndex(index+1);
        else if(windows->currentIndex()==4)
            windows->setCurrentIndex(0);
        qDebug()<<"Right";
        break;
    }
    QMainWindow::keyPressEvent(event);

}
void MainInterface::keyReleaseEvent(QKeyEvent *event)
{

      QMainWindow::keyReleaseEvent(event);
    return;
}

