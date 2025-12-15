#ifndef STUDYRECORD_H
#define STUDYRECORD_H

#include <QWidget>

#include <QtSql/QSqlQuery>

namespace Ui {
class StudyRecord;
}

class StudyRecord : public QWidget
{
    Q_OBJECT

public:
    explicit StudyRecord(QWidget *parent = nullptr,QSqlDatabase* DB=nullptr,QString USERNAME=nullptr);
    ~StudyRecord();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_importNote_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_date_dateChanged(const QDate &date);

private:
    Ui::StudyRecord *ui;
    QSqlDatabase* db;
    QString tablename;
    QString username;
};

#endif // STUDYRECORD_H
