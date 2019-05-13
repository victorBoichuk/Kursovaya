#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<add.h>
#include<doctors.h>
#include<patients.h>
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
    void patSearch();
    void dctrSearch();
    bool isPressed = false;


private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();




    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();





    void on_action_5_triggered();

    void on_action_6_triggered();

    void on_action_3_triggered();

    void on_action_7_triggered();

    void on_action_triggered();

    void on_action_12_triggered();

    void on_action_13_triggered();

private:
    Ui::MainWindow *ui;
    DatabaseConection mDbConnection;
    QSqlQueryModel *mModel;
    Add *add;
    Patients *pt;
    doctors *dct;


};

#endif // MAINWINDOW_H
