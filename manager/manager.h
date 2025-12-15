#ifndef MANAGER_H
#define MANAGER_H

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QWidget>

namespace Ui {
class Manager;
}

class Manager : public QWidget
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = nullptr,QSqlDatabase* DB=nullptr);
    ~Manager();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Manager *ui;
    QString tablename;
    QSqlDatabase* db;
    QSqlQueryModel* model;
    QList<QString>* tablenamelist;
};

#endif // MANAGER_H
