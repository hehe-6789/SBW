#include "dataanalyse.h"
#include "ui_dataanalyse.h"

#include <QSqlQuery>
#include <QSqlQueryModel>

dataAnalyse::dataAnalyse(QWidget *parent,QSqlDatabase* DB,QString USERNAME)
    : QWidget(parent)
    , db(DB)
    ,username(USERNAME)
    , ui(new Ui::dataAnalyse)
{
    ui->setupUi(this);
    this->setLayout(ui->horizontalLayout);   //窗口适应
    chart=new QChart;                        //建立图表
    QDate currentdate=QDate::currentDate();//将默认日期设为今天
    ui->dateEdit->setDate(currentdate);
    if(!db->open())                         //打开数据库
    {
        qDebug()<<"dataAnalyze open error";
    }
    else{
        qDebug()<<"dataAnalyze open success";
    }
    model=new QSqlQueryModel;

}

dataAnalyse::~dataAnalyse()
{
    delete ui;
    delete model;
}
//查询
void dataAnalyse::on_pushButton_clicked()
{
    tablename=ui->comboBox->currentText();
    if(tablename=="study")
    {
        model->clear();//清空模型
        ui->selectData->addItem("studynum");//重置分析数据选项
        ui->selectData->addItem("studytime");
        ui->selectData->addItem("studyefficiency");

        QSqlQuery query(*db);                   //获取查询内容
        QString sqlselect=QString("select year,month,day,studynum,studytime,round((studynum/studytime),2) as studyefficiency,studynote from %1 where name=? and year=? and month=? and day=?").arg(tablename);
        QDate date=ui->dateEdit->date();                    //读取日期
        QString year=QString::number(date.year()).trimmed();
        QString month=QString::number(date.month()).trimmed();
        QString day=QString::number(date.day()).trimmed();
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.addBindValue(year);
        query.addBindValue(month);
        query.addBindValue(day);
        query.exec();
        model->setQuery(query);                 //为模型赋值查询内容
        model->setHeaderData(0,Qt::Horizontal,"year"); //设置表头
        model->setHeaderData(1,Qt::Horizontal,"month");
        model->setHeaderData(2,Qt::Horizontal,"day");
        model->setHeaderData(3,Qt::Horizontal,"studynum");
        model->setHeaderData(4,Qt::Horizontal,"studytime");
        model->setHeaderData(5,Qt::Horizontal,"studyefficiency");
        model->setHeaderData(6,Qt::Horizontal,"studynote");
    }
    else if(tablename=="diary")
    {
        model->clear();
        ui->selectData->addItem("weather");
        ui->selectData->addItem("mood");
        QSqlQuery query(*db);                   //获取查询内容
        QString sqlselect=QString("select year,month,day,weather,mood,note from %1 where name=? and year=? and month=? and day=?").arg(tablename);
        QDate date=ui->dateEdit->date();                    //读取日期
        QString year=QString::number(date.year()).trimmed();
        QString month=QString::number(date.month()).trimmed();
        QString day=QString::number(date.day()).trimmed();
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.addBindValue(year);
        query.addBindValue(month);
        query.addBindValue(day);
        query.exec();
        model->setQuery(query);                 //为模型赋值查询内容
        model->setHeaderData(0,Qt::Horizontal,"year"); //设置表头
        model->setHeaderData(1,Qt::Horizontal,"month");
        model->setHeaderData(2,Qt::Horizontal,"day");
        model->setHeaderData(3,Qt::Horizontal,"weather");
        model->setHeaderData(4,Qt::Horizontal,"mood");
        model->setHeaderData(5,Qt::Horizontal,"diary");
        ui->tableView->setModel(model);           //显示表
    }
    else if(tablename=="course")
    {
        model->clear();
        QSqlQuery query(*db);                   //获取查询内容
        QString sqlselect=QString("select course,year,month,day,endyear,endmonth,endday,remain from %1 where name=? and year=? and month=? and day=?").arg(tablename);
        QDate date=ui->dateEdit->date();                    //读取日期
        QString year=QString::number(date.year()).trimmed();
        QString month=QString::number(date.month()).trimmed();
        QString day=QString::number(date.day()).trimmed();
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.addBindValue(year);
        query.addBindValue(month);
        query.addBindValue(day);


        query.exec();
        model->setQuery(query);                 //为模型赋值查询内容

        model->setHeaderData(0,Qt::Horizontal,"course"); //设置表头
        model->setHeaderData(1,Qt::Horizontal,"year"); //设置表头
        model->setHeaderData(2,Qt::Horizontal,"month");
        model->setHeaderData(3,Qt::Horizontal,"day");
        model->setHeaderData(4,Qt::Horizontal,"endyear"); //设置表头
        model->setHeaderData(5,Qt::Horizontal,"endmonth");
        model->setHeaderData(6,Qt::Horizontal,"endday");
        model->setHeaderData(7,Qt::Horizontal,"remain");
        ui->tableView->setModel(model);           //显示表
    }
    else if(tablename=="bill")
    {
        model->clear();
        QSqlQuery query(*db);                   //获取查询内容
        QString sqlselect=QString("select id,year,month,day,amount,category,method,note from %1 where name=? and year=? and month=? and day=?").arg(tablename);
        QDate date=ui->dateEdit->date();                    //读取日期
        QString year=QString::number(date.year()).trimmed();
        QString month=QString::number(date.month()).trimmed();
        QString day=QString::number(date.day()).trimmed();
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.addBindValue(year);
        query.addBindValue(month);
        query.addBindValue(day);
        query.exec();
        model->setQuery(query);                 //为模型赋值查询内容

        model->setHeaderData(0,Qt::Horizontal,"id"); //设置表头
        model->setHeaderData(1,Qt::Horizontal,"year"); //设置表头
        model->setHeaderData(2,Qt::Horizontal,"month");
        model->setHeaderData(3,Qt::Horizontal,"day");
        model->setHeaderData(4,Qt::Horizontal,"amount");
        model->setHeaderData(5,Qt::Horizontal,"category");
        model->setHeaderData(6,Qt::Horizontal,"method");
        model->setHeaderData(7,Qt::Horizontal,"note");

        ui->tableView->setModel(model);           //显示表
    }
}

//月数据分析实现
void dataAnalyse::on_pushButton_2_clicked()
{
    chart->removeAllSeries();//清理已有曲线
    tablename=ui->comboBox->currentText(); //设置数据表名
    int month=ui->dateEdit->date().month();//获取年月
    int year=ui->dateEdit->date().year();
    QSqlQuery query(*db);//获取数据
    //--------------------------------------------------------------------------------study板块
    if(tablename=="study")
    {
    QString data=ui->selectData->currentText();
    if(data!="studyefficiency")//处理非虚拟表
    {
    QString sqlselect =QString("select %1 from %2 where name=? and year=? and month=? order by day asc").arg(data).arg(tablename);//查询数据
    query.prepare(sqlselect);
    query.addBindValue(username);
    query.addBindValue(year);
    query.addBindValue(month);
    if(query.exec())
    {
        qDebug()<<"命令发送成功";
    }
    else
    {
        qDebug()<<"命令发送失败";

    }
    }
    else{                                                               //处理虚拟表
        QString sqlselect =QString("select round((studynum/studytime),2) as studyefficiency from %1 where name=? and year=? and month=? order by day asc").arg(tablename);//查询数据
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.addBindValue(year);
        query.addBindValue(month);
        if(query.exec())
        {
            qDebug()<<"命令发送成功";
        }
        else
        {
            qDebug()<<"命令发送失败";

        }
    }
    QList<int> list;                //封装数据
    while(query.next())
    {
        qDebug()<<"你好";
        list.append(query.value(data).toInt());
    }
    QLineSeries * lineseries=new QLineSeries;
    int j=0;                        //坐标轴
    for(int i:list)                 //x点坐标简易实现
    {
        lineseries->append(j,i);
        j++;
    }

    chart->addSeries(lineseries);
    chart->createDefaultAxes();
    ui->graphicsView->setChart(chart);
    }
    //-----------------------------------------------------diary
    else if(tablename=="diary"){
        QString data=ui->selectData->currentText();

            if(data=="weather")
            {
                //diary数据分析实现，绘制饼图
                QStringList list_piecolor = {
                    "#6480D6","#A1DC85","#FFAD25","#FF7777"
                };//饼图颜色
                QMap<QString,int> weathermap;
                QString sqlselect =QString("select weather,count(*) as num from %1 where name=? and year=? and month=? and weather in('晴','阴','雨','雪') group by weather").arg(tablename);//查询数据
                query.prepare(sqlselect);//晴天统计
                query.addBindValue(username);
                query.addBindValue(year);
                query.addBindValue(month);
                query.exec();
                while(query.next())
                {
                    QString weather_read=query.value("weather").toString();
                    weathermap[weather_read]=query.value("num").toInt();
                }
                QPieSeries* pie=new QPieSeries;
                qDebug()<<weathermap["晴"];
                qDebug()<<"想死";
                int j=0;
                for(auto i:weathermap.keys())
                {
                    QPieSlice* slice=new QPieSlice;
                    slice->setLabel(i);
                    slice->setValue(weathermap[i]);
                    pie->append(slice);
                }
                chart->addSeries(pie);
                ui->graphicsView->setChart(chart);
            }
            else if(data=="mood")
            {
                //mood数据分析实现，绘制饼图
                QMap<QString,int> moodmap;
                QString sqlselect =QString("select mood,count(*) as num from %1 where name=? and year=? and month=? and mood in('不知天地为何物','好','一般','坏','想死') group by mood").arg(tablename);//查询数据
                query.prepare(sqlselect);//获取数据
                query.addBindValue(username);
                query.addBindValue(year);
                query.addBindValue(month);
                query.exec();
                while(query.next())//将数据存储在map,方便使用
                {
                    QString mood_read=query.value("mood").toString();
                    moodmap[mood_read]=query.value("num").toInt();
                }
                QPieSeries* pie=new QPieSeries;
                qDebug()<<"想死";

                for(auto i:moodmap.keys())  //遍历键，为饼图块赋值并添加进入饼图
                {
                    QPieSlice* slice=new QPieSlice;
                    slice->setLabel(i);
                    slice->setValue(moodmap[i]);
                    pie->append(slice);
                }
                chart->addSeries(pie);

                ui->graphicsView->setChart(chart);

    }

}
    else if(tablename=="bill")
    {
        model->clear();
        chart->removeAllSeries();
        QSqlQuery query(*db);                   //获取查询内容
        QString sqlselect=QString("select year,month,day,SUM(amount) as netoutlay from %1 where name=? and year=? and month=? group by year,month,day order by day asc").arg(tablename);
        QDate date=ui->dateEdit->date();                    //读取日期
        QString year=QString::number(date.year()).trimmed();
        QString month=QString::number(date.month()).trimmed();
        QString day=QString::number(date.day()).trimmed();
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.addBindValue(year);
        query.addBindValue(month);
        query.exec();

        QLineSeries * lineseries=new QLineSeries;
        QMap<int,float> map;
        //画折线图
        while(query.next())
        {
            map[query.value("day").toInt()]=query.value("netoutlay").toInt();
        }
        for(auto i:map.keys())
        {
            lineseries->append(i,map[i]);
            qDebug()<<i<<":"<<map[i];
        }
        chart->addSeries(lineseries);
        chart->createDefaultAxes();
        ui->graphicsView->setChart(chart);
        model->setQuery(query);                 //为模型赋值查询内容

        model->setHeaderData(0,Qt::Horizontal,"year"); //设置表头
        model->setHeaderData(1,Qt::Horizontal,"month");
        model->setHeaderData(2,Qt::Horizontal,"day");
        model->setHeaderData(3,Qt::Horizontal,"netoutlay");


        ui->tableView->setModel(model);           //显示表


}
else if(tablename=="course")
{


}
}
//年数据分析实现
void dataAnalyse::on_pushButton_3_clicked()
{
    chart->removeAllSeries();//清理曲线
    tablename=ui->comboBox->currentText(); //设置数据表名
    int month=ui->dateEdit->date().month();
    int year=ui->dateEdit->date().year();
    QSqlQuery query(*db);//获取数据
    QString data=ui->selectData->currentText();
    //-----------------------------------------------------------------------------------study实现
    if(tablename=="study")
    {
    if(data!="studyefficiency")//处理非虚拟表
    {
    QString sqlselect =QString("select %1 from %2 where name=? and year=? order by day asc").arg(data).arg(tablename);//查询数据
    query.prepare(sqlselect);
    query.addBindValue(username);
    query.addBindValue(year);
    if(query.exec())            //检验命令发送
    {
        qDebug()<<"命令发送成功";
    }
    else
    {
        qDebug()<<"命令发送失败";
    }
    }
    else{
        QString sqlselect =QString("select round((studynum/studytime),2) as studyefficiency from %1 where name=? and year=? order by day asc").arg(tablename);//查询数据
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.addBindValue(year);
        if(query.exec())
        {
            qDebug()<<"命令发送成功";
        }
        else
        {
            qDebug()<<"命令发送失败";

        }
    }
    QList<int> list;                //封装数据
    while(query.next())
    {
        qDebug()<<"你好";
        list.append(query.value(data).toInt());
    }
    QLineSeries * lineseries=new QLineSeries;
    int j=0;                        //坐标轴
    for(int i:list)
    {
        lineseries->append(j,i);
        j++;
    }
    chart->addSeries(lineseries);
    chart->createDefaultAxes();
    ui->graphicsView->setChart(chart);
    }
    //------------------------------------------------------------------------------------diary实现
    else if(tablename=="diary")
    {
        if(data=="weather")
        {
        //diary数据分析实现，绘制饼图
        QMap<QString,int> weathermap;
        QString sqlselect =QString("select weather,count(*) as num from %1 where name=? and year=? and month=? and weather in('晴','阴','雨','雪') group by weather").arg(tablename);//查询数据
        query.prepare(sqlselect);//晴天统计
        query.addBindValue(username);
        query.addBindValue(year);
        query.addBindValue(month);
        query.exec();
        while(query.next())
        {
            QString weather_read=query.value("weather").toString();
            weathermap[weather_read]=query.value("num").toInt();
        }
        QPieSeries* pie=new QPieSeries;
        qDebug()<<weathermap["晴"];
        qDebug()<<"想死";

        for(auto i:weathermap.keys())
        {
            QPieSlice* slice=new QPieSlice;
            slice->setLabel(i);
            slice->setValue(weathermap[i]);
            pie->append(slice);
        }
        chart->addSeries(pie);
        ui->graphicsView->setChart(chart);
        }
        else if(data=="mood")
        {
            //mood数据分析实现，绘制饼图
            QMap<QString,int> moodmap;
            QString sqlselect =QString("select mood,count(*) as num from %1 where name=? and year=? and month=? and mood in('不知天地为何物','好','一般','坏','想死') group by mood").arg(tablename);//查询数据
            query.prepare(sqlselect);//获取数据
            query.addBindValue(username);
            query.addBindValue(year);
            query.addBindValue(month);
            query.exec();
            while(query.next())
            {
                QString mood_read=query.value("mood").toString();
               moodmap[mood_read]=query.value("num").toInt();
            }
            QPieSeries* pie=new QPieSeries;
            qDebug()<<"想死";

            for(auto i:moodmap.keys())
            {
                QPieSlice* slice=new QPieSlice;
                slice->setLabel(i);
                slice->setValue(moodmap[i]);
                pie->append(slice);
            }
            chart->addSeries(pie);
            ui->graphicsView->setChart(chart);
        }
        }
    else if(tablename=="bill")
    {
        model->clear();
        chart->removeAllSeries();
        QSqlQuery query(*db);                   //获取查询内容
        QString sqlselect=QString("select year,month,day,SUM(amount) as netoutlay from %1 where name=? and year=? group by year,month,day order by month,day asc").arg(tablename);
        QDate date=ui->dateEdit->date();                    //读取日期
        QString year=QString::number(date.year()).trimmed();
        QString month=QString::number(date.month()).trimmed();
        QString day=QString::number(date.day()).trimmed();
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.addBindValue(year);
        query.exec();

        QLineSeries * lineseries=new QLineSeries;
        QList<float> list;
        //画折线图
        while(query.next())
        {
            list.append(query.value("netoutlay").toInt());
        }
        int j=0;
        for(auto i:list)
        {
            lineseries->append(j,i);
            j++;
        }
        chart->addSeries(lineseries);
        chart->createDefaultAxes();
        ui->graphicsView->setChart(chart);
        model->setQuery(query);                 //为模型赋值查询内容

        model->setHeaderData(0,Qt::Horizontal,"year"); //设置表头
        model->setHeaderData(1,Qt::Horizontal,"month");
        model->setHeaderData(2,Qt::Horizontal,"day");
        model->setHeaderData(3,Qt::Horizontal,"netoutlay");


        ui->tableView->setModel(model);           //显示表
        }
    }



//切换数据类型
void dataAnalyse::on_comboBox_currentTextChanged(const QString &arg1)
{
    chart->removeAllSeries();//擦除当前曲线
    tablename=ui->comboBox->currentText();//获取当前数据表
    ui->tableView->setModel(NULL);
    if(tablename=="study")
    {
        ui->selectData->clear();
        model->clear();//清空模型
        ui->selectData->addItem("studynum");//重置分析数据选项
        ui->selectData->addItem("studytime");
        ui->selectData->addItem("studyefficiency");

        QSqlQuery query(*db);                   //获取查询内容
        QString sqlselect=QString("select year,month,day,round(studynum,2) as studynum,studytime,round((studynum/studytime),2) as studyefficiency,studynote from %1 where name=?").arg(tablename);
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.exec();
        model->setQuery(query);                 //为模型赋值查询内容
        model->setHeaderData(0,Qt::Horizontal,"year"); //设置表头
        model->setHeaderData(1,Qt::Horizontal,"month");
        model->setHeaderData(2,Qt::Horizontal,"day");
        model->setHeaderData(3,Qt::Horizontal,"studynum");
        model->setHeaderData(4,Qt::Horizontal,"studytime");
        model->setHeaderData(5,Qt::Horizontal,"studyefficiency");
        model->setHeaderData(6,Qt::Horizontal,"studynote");
        ui->tableView->setModel(model);           //显示表
    }
    else if(tablename=="diary")
    {
     ui->selectData->clear();
        model->clear();
        ui->selectData->addItem("weather");
        ui->selectData->addItem("mood");
        QSqlQuery query(*db);                   //获取查询内容
        QString sqlselect=QString("select year,month,day,weather,mood,note from %1 where name=?").arg(tablename);
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.exec();
        model->setQuery(query);                 //为模型赋值查询内容
        model->setHeaderData(0,Qt::Horizontal,"year"); //设置表头
        model->setHeaderData(1,Qt::Horizontal,"month");
        model->setHeaderData(2,Qt::Horizontal,"day");
        model->setHeaderData(3,Qt::Horizontal,"weather");
        model->setHeaderData(4,Qt::Horizontal,"mood");
        model->setHeaderData(5,Qt::Horizontal,"diary");
        ui->tableView->setModel(model);           //显示表
    }
    else if(tablename=="bill"){
        ui->selectData->clear();
        ui->selectData->addItem("netoutlay");
        model->clear();
        QSqlQuery query(*db);                   //获取查询内容
        QString sqlselect=QString("select id,year,month,day,amount,category,method,note from %1 where name=?").arg(tablename);
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.exec();
        model->setQuery(query);                 //为模型赋值查询内容

        model->setHeaderData(0,Qt::Horizontal,"id"); //设置表头
        model->setHeaderData(1,Qt::Horizontal,"year"); //设置表头
        model->setHeaderData(2,Qt::Horizontal,"month");
        model->setHeaderData(3,Qt::Horizontal,"day");
        model->setHeaderData(4,Qt::Horizontal,"amount");
        model->setHeaderData(5,Qt::Horizontal,"category");
        model->setHeaderData(6,Qt::Horizontal,"method");
        model->setHeaderData(7,Qt::Horizontal,"note");

        ui->tableView->setModel(model);           //显示表

    }
    else if(tablename=="course")
    {
      ui->selectData->clear();
        ui->selectData->clear();
        model->clear();
        ui->selectData->addItem("");
        QSqlQuery query(*db);                   //获取查询内容
        QString sqlselect=QString("select course,year,month,day,endyear,endmonth,endday,remain from %1 where name=?").arg(tablename);
        query.prepare(sqlselect);
        query.addBindValue(username);
        query.exec();
        model->setQuery(query);                 //为模型赋值查询内容

        model->setHeaderData(0,Qt::Horizontal,"course"); //设置表头
        model->setHeaderData(1,Qt::Horizontal,"year"); //设置表头
        model->setHeaderData(2,Qt::Horizontal,"month");
        model->setHeaderData(3,Qt::Horizontal,"day");
        model->setHeaderData(4,Qt::Horizontal,"endyear"); //设置表头
        model->setHeaderData(5,Qt::Horizontal,"endmonth");
        model->setHeaderData(6,Qt::Horizontal,"endday");
        model->setHeaderData(7,Qt::Horizontal,"remain");
        ui->tableView->setModel(model);           //显示表
    }
}


void dataAnalyse::on_selectData_currentTextChanged(const QString &arg1)
{
    chart->removeAllSeries();
}

