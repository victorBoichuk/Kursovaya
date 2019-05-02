#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<search.h>
#include <QMainWindow>
#include "databaseconection.h"
#include <QDate>
#include<QTextBrowser>



namespace Ui {
class MainWindow;
}

class QSqlQueryModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QDate lastdate,nextdate,date1,date2,date3,date4,date5,date6;

    void getDayOfWeek();
    void getFirstDay();
    void getSecondDay();
    void getThirdDay();
    void getFourthDay();
    void getFifthDay();
    void getSixthDay();
    void search();



private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();


private:
    Ui::MainWindow *ui;
    DatabaseConection mDbConnection;
    QSqlQueryModel *mModel;


};

#endif // MAINWINDOW_H
