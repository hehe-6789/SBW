#ifndef BILLRECORD_H
#define BILLRECORD_H

#include <QDoubleValidator>
#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class BillRecord;
}

class BillRecord : public QMainWindow
{
    Q_OBJECT

public:
    explicit BillRecord(QWidget *parent = nullptr,
                        QSqlDatabase *DB = nullptr,
                        QString USERNAME = nullptr);
    ~BillRecord();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_type_currentTextChanged(const QString &arg1);

private:
    Ui::BillRecord *ui;
    QSqlDatabase *db;
    QString username;
    QString tablename;
    QDoubleValidator *validator;
    QDoubleValidator *validator2;

};

#endif // BILLRECORD_H
