#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QSqlQuery>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,QSqlDatabase *DB=nullptr);
    QSqlDatabase* db;
    QString tablename;          //表名
    QPixmap octo;               //图片
    QString username;           //用户名
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
