#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include <QSqlQueryModel>
#include<QSqlQuery>
#include <QDate>
#include<search.h>
#include <QTableWidget>
#include<QTableWidgetItem>

#define lbl label

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mDbConnection("MySQLServer","SQL SERVER","Kursovaya",true)
{
    QString error;
    if (!mDbConnection.openDatabase(&error))
    {
        QMessageBox::critical(this, "Error", error);
        return;
    }

    ui->setupUi(this);
    mModel = nullptr;
/*
    if (mModel==nullptr){
        mModel = new QSqlQueryModel(this);
        mModel->setQuery("SELECT* FROM Doctors");
       ui->tableView->setModel(mModel);
       ui->tableView->setAutoScroll(true);
    }*/
     date1.setDate(2019,4,22);
     lastdate.setDate(2019,4,22);
     nextdate.setDate(2019,4,28);
     date2=date1.addDays(1);
     date3=date1.addDays(2);
     date4=date1.addDays(3);
     date5=date1.addDays(4);
     date6=date1.addDays(5);
     ui->patient->setPlaceholderText("Имя пациента");
     ui->doctor->setPlaceholderText("Имя врача");
     ui->cabinet->setPlaceholderText("№ кабинета");


     ui->tableWidget_7->hide();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::search(){
    ui->tableWidget_7->show();
    ui->frame_18->hide();
    QString Pat = ui->patient->text();
    QString Dctr = ui->doctor->text();
    QString Cab = ui->cabinet->text();
    QString Dat = "";

    QString patN, dctN;;


    if (Pat.length()!=0){
        const QString queryStr = QString::fromUtf8("Select Номер_пациента from Patients where ФИО like '%1%'").arg(Pat);
        QSqlQuery selectt;
        selectt.exec(queryStr);
        while(selectt.next()){
        patN+= selectt.value(0).toString()+"\n";
        }
    }

    if (Dctr.length()!=0){
        const QString queryStr1 = QString::fromUtf8("Select Табельный_номер from Doctors where ФИО like '%1%'").arg(Dctr);
        QSqlQuery selectt1;
        selectt1.exec(queryStr1);
        while(selectt1.next()){
        dctN+= selectt1.value(0).toString()+"\n";
        }
    }

    QString filter_dct = "Табельный_номер LIKE'"+dctN[0]+"'";
    QString filter_pat = "Номер_пациента LIKE'"+patN[0]+"'";
    QString filter_cab = "Номер_кабинета LIKE'"+Cab+"'";
    QString filter_date = "Дата LIKE'"+Dat+"'";

    QString text;
    if( Pat.length() != 0 )
      text.append(filter_pat);

    if( Dctr.length() != 0 )
    {
      if( text.length() != 0 )
        text.append( " and " );
      text.append( filter_dct);
    }

    if( Cab.length() != 0 )
    {
      if( text.length() != 0 )
        text.append( " and " );
      text.append( filter_cab );
    }

    if( Dat.length() != 0 )
    {
      if( text.length() != 0 )
        text.append( " and " );
      text.append( filter_date );
    }

    if (text.length()!=0){
        QString doctorN, patientN, Cabinet, Date, Time;
        const QString queryStr2 = QString::fromUtf8("Select Табельный_номер, Номер_пациента, Дата, Время, Номер_кабинета from TimeTable where %1").arg(text);
        QSqlQuery selectt2;
        int i=0;
        selectt2.exec(queryStr2);
        while(selectt2.next()){
        doctorN+= selectt2.value(0).toString()+"\n";
        patientN+= selectt2.value(1).toString()+"\n";
        Date+= selectt2.value(2).toString()+"\n";
        Time+= selectt2.value(3).toString()+"\n";
        Cabinet+= selectt2.value(4).toString()+"\n";
        i++;
        }
        int a=0, b=0, c=0 ,d=0, e=0, jj=0, ii=0;
        QString A, B, C, D, E;
        QFont fnt;
        fnt.setFamily("verdana");
        QString dctr, pat;
        ui->tableWidget_7->setRowCount(1);
        ui->tableWidget_7->setColumnCount(i);
        for(int col = 0; col < i; ++col){
            for (int hj=a; hj<2+a;hj++){
                if (doctorN[hj]!='\n'){
                    A+=doctorN[hj];
                }
            }
            for (int jh=b; jh<2+b;jh++){
                if (patientN[jh]!='\n'){
                    B+=patientN[jh];
                }
            }
           for(int g=0+c-jj; g<3+c-jj; g++){
               C+=Cabinet[g];
           }

           for (int  h=0+d-ii; h<5+d-ii; h++){
               D+=Time[h];
           }

           for (int  hm=0+e-ii; hm<10+e-ii; hm++){
               E+=Date[hm];
           }


           const QString queryStr1 = QString::fromUtf8("Select ФИО from Doctors Where Табельный_номер = %1").arg(A);
           QSqlQuery selectt1;
           selectt1.exec(queryStr1);
           if(selectt1.next()){
           dctr = selectt1.value(0).toString()+"\n";
           }

           const QString queryStr2 = QString::fromUtf8("Select ФИО from Patients Where Номер_пациента = %1").arg(B);
           QSqlQuery selectt2;
           selectt2.exec(queryStr2);
           if(selectt2.next()){
           pat = selectt2.value(0).toString()+"\n";
           }


            /*if (row%2==0){
              ui->tableWidget->item(row,0)->setBackgroundColor(Qt::red);
            }*/

            ui->tableWidget_7->setItem(0, col, new QTableWidgetItem("Врач:\n"+dctr+"\nПациент:\n"+pat+"\nКабинет:\n"+C+"\n\nВремя:\n"+D+"\nДата:\n"+E));
            ui->tableWidget_7->item(0,col)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_7->item(0,col)->setFont(fnt);
            a+=2;
            b+=2;
            c+=5;
            d+=18;
            e+=10;
            A.clear();
            B.clear();
            C.clear();
            D.clear();
            E.clear();
            jj++;
            ii++;
            }
        ui->tableWidget_7->verticalHeader()->hide();
        ui->tableWidget_7->horizontalHeader()->hide();
        ui->tableWidget_7->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->tableWidget_7->resizeRowsToContents();
        ui->tableWidget_7->resizeColumnsToContents();
        ui->tableWidget_7->scrollToBottom();
        ui->tableWidget_7->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }else {
        QMessageBox::warning(this, "Ошибка","Поля поиска пусты");
    }

}


void MainWindow::getDayOfWeek(){
       ui->label_10->setText(QString::number(date1.day())+" "+QDate::shortMonthName(date1.month()));
       ui->label_11->setText(QString::number(date2.day())+" "+QDate::shortMonthName(date2.month()));
       ui->label_12->setText(QString::number(date3.day())+" "+QDate::shortMonthName(date3.month()));
       ui->label_13->setText(QString::number(date4.day())+" "+QDate::shortMonthName(date4.month()));
       ui->label_14->setText(QString::number(date5.day())+" "+QDate::shortMonthName(date5.month()));
       ui->label_15->setText(QString::number(date6.day())+" "+QDate::shortMonthName(date6.month()));
       ui->label->setText(QString::number(lastdate.day())+" "+QDate::shortMonthName(lastdate.month())+" "+QString::number(lastdate.year()));
       ui->label_2->setText(QString::number(nextdate.day())+" "+QDate::shortMonthName(nextdate.month())+" "+QString::number(nextdate.year()));
}


void MainWindow::getFirstDay(){
    QString dctN, ptN, cab, tm;
    const QString queryStr = QString::fromUtf8("Select Табельный_номер,Номер_пациента, Номер_кабинета, Время from TimeTable where Дата ='%1'").arg(date1.toString("yyyy-MM-dd"));
    QSqlQuery selectt;
    selectt.exec(queryStr);
    int i=0;
    while(selectt.next()){
    dctN += selectt.value(0).toString()+"\n";
    ptN += selectt.value(1).toString()+"\n";
    cab += selectt.value(2).toString()+"\n";
    tm += selectt.value(3).toString()+"\n";
    i++;
    }

    int a=0,b=0,c=0,d=0,jj=0,ii=0;
    QString A, B, C, D;
    QFont fnt;
    fnt.setFamily("verdana");
    QString dctr, pat;
    ui->tableWidget->setRowCount(i);
    ui->tableWidget->setColumnCount(1);
    for(int row = 0; row < i; ++row){
       A=dctN[a];
       B=ptN[b];
       for(int g=0+c-jj; g<3+c-jj; g++){
           C+=cab[g];
       }

       for (int  h=0+d-ii; h<5+d-ii; h++){
           D+=tm[h];
       }

       const QString queryStr1 = QString::fromUtf8("Select ФИО from Doctors Where Табельный_номер = %1").arg(A);
       QSqlQuery selectt1;
       selectt1.exec(queryStr1);
       if(selectt1.next()){
       dctr = selectt1.value(0).toString()+"\n";
       }

       const QString queryStr2 = QString::fromUtf8("Select ФИО from Patients Where Номер_пациента = %1").arg(B);
       QSqlQuery selectt2;
       selectt2.exec(queryStr2);
       if(selectt2.next()){
       pat = selectt2.value(0).toString()+"\n";
       }


        /*if (row%2==0){
          ui->tableWidget->item(row,0)->setBackgroundColor(Qt::red);
        }*/

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem("Врач:\n"+dctr+"\nПациент:\n"+pat+"\nКабинет:\n"+C+"\n\nВремя:\n"+D));
        ui->tableWidget->item(row,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(row,0)->setFont(fnt);
        a+=2;
        b+=2;
        c+=5;
        d+=18;
        C.clear();
        D.clear();
        jj++;
        ii++;
        }
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->scrollToBottom();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::getSecondDay(){
    QString dctN, ptN, cab, tm;
    const QString queryStr = QString::fromUtf8("Select Табельный_номер,Номер_пациента, Номер_кабинета, Время from TimeTable where Дата ='%1'").arg(date2.toString("yyyy-MM-dd"));
    QSqlQuery selectt;
    selectt.exec(queryStr);
    int i=0;
    QFont fnt;
    fnt.setFamily("verdana");
    while(selectt.next()){
    dctN += selectt.value(0).toString()+"\n";
    ptN += selectt.value(1).toString()+"\n";
    cab += selectt.value(2).toString()+"\n";
    tm += selectt.value(3).toString()+"\n";
    i++;
    }

    int a=0,b=0,c=0,d=0,jj=0,ii=0;
    QString A, B, C, D;
    QString dctr, pat;
    ui->tableWidget_2->setRowCount(i);
    ui->tableWidget_2->setColumnCount(1);
    for(int row = 0; row < i; ++row){
       A=dctN[a];
       B=ptN[b];
       for(int g=0+c-jj; g<3+c-jj; g++){
           C+=cab[g];
       }

       for (int  h=0+d-ii; h<5+d-ii; h++){
           D+=tm[h];
       }

       const QString queryStr1 = QString::fromUtf8("Select ФИО from Doctors Where Табельный_номер = %1").arg(A);
       QSqlQuery selectt1;
       selectt1.exec(queryStr1);
       if(selectt1.next()){
       dctr = selectt1.value(0).toString()+"\n";
       }

       const QString queryStr2 = QString::fromUtf8("Select ФИО from Patients Where Номер_пациента = %1").arg(B);
       QSqlQuery selectt2;
       selectt2.exec(queryStr2);
       if(selectt2.next()){
       pat = selectt2.value(0).toString()+"\n";
       }



       ui->tableWidget_2->setItem(row, 0, new QTableWidgetItem("Врач:\n"+dctr+"\nПациент:\n"+pat+"\nКабинет:\n"+C+"\n\nВремя:\n"+D));
       ui->tableWidget_2->item(row,0)->setTextAlignment(Qt::AlignCenter);
       ui->tableWidget_2->item(row,0)->setFont(fnt);
        a+=2;
        b+=2;
        c+=5;
        d+=18;
        C.clear();
        D.clear();
        jj++;
        ii++;
        }
    ui->tableWidget_2->verticalHeader()->hide();
    ui->tableWidget_2->horizontalHeader()->hide();
    ui->tableWidget_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget_2->resizeRowsToContents();
    ui->tableWidget_2->scrollToBottom();
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::getThirdDay(){
    QString dctN, ptN, cab, tm;
    const QString queryStr = QString::fromUtf8("Select Табельный_номер,Номер_пациента, Номер_кабинета, Время from TimeTable where Дата ='%1'").arg(date3.toString("yyyy-MM-dd"));
    QSqlQuery selectt;
    selectt.exec(queryStr);
    int i=0;
    while(selectt.next()){
    dctN += selectt.value(0).toString()+"\n";
    ptN += selectt.value(1).toString()+"\n";
    cab += selectt.value(2).toString()+"\n";
    tm += selectt.value(3).toString()+"\n";
    i++;
    }
    QFont fnt;
    fnt.setFamily("verdana");

    int a=0,b=0,c=0,d=0,jj=0,ii=0;
    QString A, B, C, D;
    QString dctr, pat;
    ui->tableWidget_3->setRowCount(i);
    ui->tableWidget_3->setColumnCount(1);
    for(int row = 0; row < i; ++row){
       A=dctN[a];
       B=ptN[b];
       for(int g=0+c-jj; g<3+c-jj; g++){
           C+=cab[g];
       }

       for (int  h=0+d-ii; h<5+d-ii; h++){
           D+=tm[h];
       }

       const QString queryStr1 = QString::fromUtf8("Select ФИО from Doctors Where Табельный_номер = %1").arg(A);
       QSqlQuery selectt1;
       selectt1.exec(queryStr1);
       if(selectt1.next()){
       dctr = selectt1.value(0).toString()+"\n";
       }

       const QString queryStr2 = QString::fromUtf8("Select ФИО from Patients Where Номер_пациента = %1").arg(B);
       QSqlQuery selectt2;
       selectt2.exec(queryStr2);
       if(selectt2.next()){
       pat = selectt2.value(0).toString()+"\n";
       }



       ui->tableWidget_3->setItem(row, 0, new QTableWidgetItem("Врач:\n"+dctr+"\nПациент:\n"+pat+"\nКабинет:\n"+C+"\n\nВремя:\n"+D));
       ui->tableWidget_3->item(row,0)->setTextAlignment(Qt::AlignCenter);
       ui->tableWidget_3->item(row,0)->setFont(fnt);
        a+=2;
        b+=2;
        c+=5;
        d+=18;
        C.clear();
        D.clear();
        jj++;
        ii++;
        }
    ui->tableWidget_3->verticalHeader()->hide();
    ui->tableWidget_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget_3->horizontalHeader()->hide();
    ui->tableWidget_3->resizeRowsToContents();
    ui->tableWidget_3->scrollToBottom();
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::getFourthDay(){
    QString dctN, ptN, cab, tm;
    const QString queryStr = QString::fromUtf8("Select Табельный_номер,Номер_пациента, Номер_кабинета, Время from TimeTable where Дата ='%1'").arg(date4.toString("yyyy-MM-dd"));
    QSqlQuery selectt;
    selectt.exec(queryStr);
    int i=0;
    QFont fnt;
    fnt.setFamily("verdana");
    while(selectt.next()){
    dctN += selectt.value(0).toString()+"\n";
    ptN += selectt.value(1).toString()+"\n";
    cab += selectt.value(2).toString()+"\n";
    tm += selectt.value(3).toString()+"\n";
    i++;
    }

    int a=0,b=0,c=0,d=0,jj=0,ii=0;
    QString A, B, C, D;
    QString dctr, pat;
    ui->tableWidget_4->setRowCount(i);
    ui->tableWidget_4->setColumnCount(1);
    for(int row = 0; row < i; ++row){
       A=dctN[a];
       B=ptN[b];
       for(int g=0+c-jj; g<3+c-jj; g++){
           C+=cab[g];
       }

       for (int  h=0+d-ii; h<5+d-ii; h++){
           D+=tm[h];
       }

       const QString queryStr1 = QString::fromUtf8("Select ФИО from Doctors Where Табельный_номер = %1").arg(A);
       QSqlQuery selectt1;
       selectt1.exec(queryStr1);
       if(selectt1.next()){
       dctr = selectt1.value(0).toString()+"\n";
       }

       const QString queryStr2 = QString::fromUtf8("Select ФИО from Patients Where Номер_пациента = %1").arg(B);
       QSqlQuery selectt2;
       selectt2.exec(queryStr2);
       if(selectt2.next()){
       pat = selectt2.value(0).toString()+"\n";
       }


       ui->tableWidget_4->setItem(row, 0, new QTableWidgetItem("Врач:\n"+dctr+"\nПациент:\n"+pat+"\nКабинет:\n"+C+"\n\nВремя:\n"+D));
       ui->tableWidget_4->item(row,0)->setTextAlignment(Qt::AlignCenter);
       ui->tableWidget_4->item(row,0)->setFont(fnt);
        a+=2;
        b+=2;
        c+=5;
        d+=18;
        C.clear();
        D.clear();
        jj++;
        ii++;
        }
    ui->tableWidget_4->verticalHeader()->hide();
    ui->tableWidget_4->horizontalHeader()->hide();
    ui->tableWidget_4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget_4->resizeRowsToContents();
    ui->tableWidget_4->scrollToBottom();
    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::getFifthDay(){
    QString dctN, ptN, cab, tm;
    const QString queryStr = QString::fromUtf8("Select Табельный_номер,Номер_пациента, Номер_кабинета, Время from TimeTable where Дата ='%1'").arg(date5.toString("yyyy-MM-dd"));
    QSqlQuery selectt;
    selectt.exec(queryStr);
    int i=0;
    QFont fnt;
    fnt.setFamily("verdana");
    while(selectt.next()){
    dctN += selectt.value(0).toString()+"\n";
    ptN += selectt.value(1).toString()+"\n";
    cab += selectt.value(2).toString()+"\n";
    tm += selectt.value(3).toString()+"\n";
    i++;
    }

    int a=0,b=0,c=0,d=0,jj=0,ii=0;
    QString A, B, C, D;
    QString dctr, pat;
    ui->tableWidget_5->setRowCount(i);
    ui->tableWidget_5->setColumnCount(1);
    for(int row = 0; row < i; ++row){
       A=dctN[a];
       B=ptN[b];
       for(int g=0+c-jj; g<3+c-jj; g++){
           C+=cab[g];
       }

       for (int  h=0+d-ii; h<5+d-ii; h++){
           D+=tm[h];
       }

       const QString queryStr1 = QString::fromUtf8("Select ФИО from Doctors Where Табельный_номер = %1").arg(A);
       QSqlQuery selectt1;
       selectt1.exec(queryStr1);
       if(selectt1.next()){
       dctr = selectt1.value(0).toString()+"\n";
       }

       const QString queryStr2 = QString::fromUtf8("Select ФИО from Patients Where Номер_пациента = %1").arg(B);
       QSqlQuery selectt2;
       selectt2.exec(queryStr2);
       if(selectt2.next()){
       pat = selectt2.value(0).toString()+"\n";
       }


       ui->tableWidget_5->setItem(row, 0, new QTableWidgetItem("Врач:\n"+dctr+"\nПациент:\n"+pat+"\nКабинет:\n"+C+"\n\nВремя:\n"+D));
       ui->tableWidget_5->item(row,0)->setTextAlignment(Qt::AlignCenter);
       ui->tableWidget_5->item(row,0)->setFont(fnt);
        a+=2;
        b+=2;
        c+=5;
        d+=18;
        C.clear();
        D.clear();
        jj++;
        ii++;
        }
    ui->tableWidget_5->verticalHeader()->hide();
    ui->tableWidget_5->horizontalHeader()->hide();
    ui->tableWidget_5->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget_5->resizeRowsToContents();
    ui->tableWidget_5->scrollToBottom();
    ui->tableWidget_5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::getSixthDay(){
    QString dctN, ptN, cab, tm;
    const QString queryStr = QString::fromUtf8("Select Табельный_номер,Номер_пациента, Номер_кабинета, Время from TimeTable where Дата ='%1'").arg(date6.toString("yyyy-MM-dd"));
    QSqlQuery selectt;
    selectt.exec(queryStr);
    int i=0;
    QFont fnt;
    fnt.setFamily("verdana");
    while(selectt.next()){
    dctN += selectt.value(0).toString()+"\n";
    ptN += selectt.value(1).toString()+"\n";
    cab += selectt.value(2).toString()+"\n";
    tm += selectt.value(3).toString()+"\n";
    i++;
    }

    int a=0,b=0,c=0,d=0,jj=0,ii=0;
    QString A, B, C, D;
    QString dctr, pat;
    ui->tableWidget_6->setRowCount(i);
    ui->tableWidget_6->setColumnCount(1);
    for(int row = 0; row < i; ++row){
       A=dctN[a];
       B=ptN[b];
       for(int g=0+c-jj; g<3+c-jj; g++){
           C+=cab[g];
       }

       for (int  h=0+d-ii; h<5+d-ii; h++){
           D+=tm[h];
       }

       const QString queryStr1 = QString::fromUtf8("Select ФИО from Doctors Where Табельный_номер = %1").arg(A);
       QSqlQuery selectt1;
       selectt1.exec(queryStr1);
       if(selectt1.next()){
       dctr = selectt1.value(0).toString()+"\n";
       }

       const QString queryStr2 = QString::fromUtf8("Select ФИО from Patients Where Номер_пациента = %1").arg(B);
       QSqlQuery selectt2;
       selectt2.exec(queryStr2);
       if(selectt2.next()){
       pat = selectt2.value(0).toString()+"\n";
       }



       ui->tableWidget_6->setItem(row, 0, new QTableWidgetItem("Врач:\n"+dctr+"\nПациент:\n"+pat+"\nКабинет:\n"+C+"\n\nВремя:\n"+D));
       ui->tableWidget_6->item(row,0)->setTextAlignment(Qt::AlignCenter);
       ui->tableWidget_6->item(row,0)->setFont(fnt);
        a+=2;
        b+=2;
        c+=5;
        d+=18;
        C.clear();
        D.clear();
        jj++;
        ii++;
        }
    ui->tableWidget_6->verticalHeader()->hide();
    ui->tableWidget_6->horizontalHeader()->hide();
    ui->tableWidget_6->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget_6->resizeRowsToContents();
    ui->tableWidget_6->scrollToBottom();
    ui->tableWidget_6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_pushButton_2_clicked()
{

    date1=date1.addDays(7);
    date2=date2.addDays(7);
    date3=date3.addDays(7);
    date4=date4.addDays(7);
    date5=date5.addDays(7);
    date6=date6.addDays(7);
    lastdate=lastdate.addDays(7);
    nextdate=nextdate.addDays(7);
    getDayOfWeek();
    getFirstDay();
    getSecondDay();
    getThirdDay();
    getFourthDay();
    getFifthDay();
    getSixthDay();
}

void MainWindow::on_pushButton_clicked()
{
    date1=date1.addDays(-7);
    date2=date2.addDays(-7);
    date3=date3.addDays(-7);
    date4=date4.addDays(-7);
    date5=date5.addDays(-7);
    date6=date6.addDays(-7);
    lastdate=lastdate.addDays(-7);
    nextdate=nextdate.addDays(-7);
    getDayOfWeek();
    getFirstDay();
    getSecondDay();
    getThirdDay();
    getFourthDay();
    getFifthDay();
    getSixthDay();
}

void MainWindow::on_pushButton_3_clicked()
{

    search();
}

