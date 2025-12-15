#ifndef DIARY_H
#define DIARY_H

#include <QSqlDatabase>
#include <QWidget>

namespace Ui {
class Diary;
}

class Diary : public QWidget
{
    Q_OBJECT

public:
    explicit Diary(QWidget *parent=nullptr, QSqlDatabase *DB=nullptr, QString USERNAME=nullptr);
    ~Diary();

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_importNote_clicked();

    void on_pushButton_5_clicked();

    void on_date_dateChanged(const QDate &date);

private:
    Ui::Diary *ui;
    QSqlDatabase* db;
    QString username;
    QString tablename;
};

#endif // DIARY_H
