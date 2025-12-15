#ifndef ENGLISHRECORD_H
#define ENGLISHRECORD_H

#include <QSqlDatabase>
#include <QWidget>

namespace Ui {
class EnglishRecord;
}

class EnglishRecord : public QWidget
{
    Q_OBJECT

public:
    explicit EnglishRecord(QWidget *parent = nullptr,QSqlDatabase*DB=nullptr,QString USERNAME=nullptr);
    ~EnglishRecord();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::EnglishRecord *ui;
    QSqlDatabase* db;
    QString username;
    QString tablename;
};

#endif // ENGLISHRECORD_H
