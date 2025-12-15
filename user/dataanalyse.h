#ifndef DATAANALYSE_H
#define DATAANALYSE_H
#include <QtCharts>
#include <QSqlDatabase>
#include <QWidget>
#include<QSqlQueryModel>
QT_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_END_NAMESPACE

namespace Ui {
class dataAnalyse;
}

class dataAnalyse : public QWidget
{
    Q_OBJECT

public:
    explicit dataAnalyse(QWidget *parent = nullptr,QSqlDatabase* DB=nullptr,QString USERNAME=nullptr);
    ~dataAnalyse();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_selectData_currentTextChanged(const QString &arg1);

private:
    Ui::dataAnalyse *ui;
    QSqlDatabase* db;
    QChart* chart;
    QString username;
    QString tablename;
    QSqlQueryModel* model;
};

#endif // DATAANALYSE_H
