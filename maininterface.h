#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include "user/billrecord.h"
#include "user/dataanalyse.h"
#include "user/diary.h"
#include "user/englishrecord.h"
#include "user/studyrecord.h"
#include <QMainWindow>
#include <QStackedWidget>
#include<QKeyEvent>
namespace Ui {
class MainInterface;
}

class MainInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainInterface(QWidget *parent = nullptr,QSqlDatabase* DB=nullptr,QString USERNAME=nullptr);
    ~MainInterface();
    QSqlDatabase*db;
    QString username;
    QStackedWidget* windows;//用于操作堆叠界面
    StudyRecord* studyRecord;//子界面
    Diary*diary;
    EnglishRecord*englishRecord;
    BillRecord* billRecord;
    dataAnalyse* dataanalyse;

private slots:
    void on_actionstudy_triggered();


    void on_actionbill_triggered();

    void on_actionEnglish_triggered();

    void on_actiondataanalyze_triggered();

    void on_actionocto_triggered();

    void on_actiondiary_triggered();

    void keyPressEvent(QKeyEvent *event); //键盘按下事件
    void keyReleaseEvent(QKeyEvent *event);//键盘松开事件
private:
    Ui::MainInterface *ui;
    void initInterface();
};

#endif // MAININTERFACE_H
