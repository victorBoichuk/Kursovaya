#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include <QSqlQueryModel>
#include<QSqlQuery>
#include <QDate>
#include<add.h>
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

    if (mModel==nullptr){
        mModel = new QSqlQueryModel(this);
    }
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

     //ui->dateEdit->setEnabled(false);
     //ui->dateEdit->setSpecialValueText( " " );
     ui->dateEdit->setDate(QDate::currentDate());
     ui->tableWidget_7->hide();
     add = new Add();
     connect(add, &Add::firstWindow, this, &MainWindow::show);

     pt = new Patients();
     connect(pt, &Patients::firstWindow, this, &MainWindow::show);

     dct = new doctors();
     connect(dct, &doctors::firstWindow,this, &MainWindow::show);

     ui->tableView->hide();


     getDayOfWeek();
     getFirstDay();
     getSecondDay();
     getThirdDay();
     getFourthDay();
     getFifthDay();
     getSixthDay();

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::search(){
    QString Dat;
    ui->tableWidget_7->show();
    ui->frame_18->hide();
    QString Pat = ui->patient->text();
    QString Dctr = ui->doctor->text();
    QString Cab = ui->cabinet->text();
    if (isPressed){
        Dat = ui->dateEdit->text();
    }else {
        Dat = "";
    }

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

           for (int  hm=0+e+ii; hm<10+e+ii; hm++){
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

            ui->tableWidget_7->setItem(0, col, new QTableWidgetItem("Врач:\n"+dctr+"\nПациент:\n"+pat+"\nКабинет:\n"+C+"\n\nВремя:\n"+D+"\n\nДата:\n"+E));
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
    ui->tableWidget_7->hide();
    ui->frame_18->show();
    ui->tableView->hide();

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
    ui->tableWidget_7->hide();
    ui->frame_18->show();
    ui->tableView->hide();

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




void MainWindow::on_pushButton_6_clicked()
{
    isPressed=true;
    ui->pushButton_6->hide();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->tableWidget_7->hide();
    ui->frame_18->show();
    ui->tableView->hide();
    ui->patient->clear();
    ui->doctor->clear();
    ui->cabinet->clear();
    isPressed=false;
    ui->pushButton_6->show();

    getDayOfWeek();
    getFirstDay();
    getSecondDay();
    getThirdDay();
    getFourthDay();
    getFifthDay();
    getSixthDay();
}

void MainWindow::on_pushButton_5_clicked()
{
    bool Nw;

    Add ad;
    ad.exec();

    QString patN, dctN;

    QString patName=ad.PatientName();
    QString dctName=ad.DoctorName();
    QString cabNmb=ad.NCabinet();
    QString dateZ=ad.DateZapisi();
    QString time=ad.Time();
    QString passport=ad.Passport();
    QString address=ad.Address();
    QString strahovk=ad.Strahovka();
    QString bornDate=ad.BornDate();
    Nw=ad.New;

    if (patName.length()!=0){
        const QString queryStr = QString::fromUtf8("Select Номер_пациента, ФИО from Patients where ФИО like '%1%'").arg(patName);
        QSqlQuery selectt;
        selectt.exec(queryStr);
        while(selectt.next()){
        patN+= selectt.value(0).toString();
        }
    }

    if (dctName.length()!=0){
        const QString queryStr1 = QString::fromUtf8("Select Табельный_номер from Doctors where ФИО like '%1%'").arg(dctName);
        QSqlQuery selectt1;
        selectt1.exec(queryStr1);
        while(selectt1.next()){
        dctN+= selectt1.value(0).toString();
        }
    }

    if (!Nw){
        const QString queryStr2 = QString::fromUtf8("Insert into TimeTable (Табельный_номер, Номер_пациента, Номер_кабинета,Дата, Время) values ('%1','%2','%3','%4','%5');").arg(dctN).arg(patN).arg(cabNmb).arg(dateZ).arg(time);
       mModel->setQuery(queryStr2);
    }else {
        const QString queryStr3 = QString::fromUtf8("Insert into Patients (ФИО, Дата_рождения, Адрес, Поспортые_данные, Номер_страхового_полиса) values ('%1','%2','%3','%4','%5');").arg(patName).arg(bornDate).arg(address).arg(passport).arg(strahovk);
        mModel->setQuery(queryStr3);

        if (patName.length()!=0){
            const QString queryStr4 = QString::fromUtf8("Select Номер_пациента from Patients where ФИО like '%1%'").arg(patName);
            QSqlQuery selectt4;
            selectt4.exec(queryStr4);
            while(selectt4.next()){
            patN+= selectt4.value(0).toString();
            }
        }
        const QString queryStr5 = QString::fromUtf8("Insert into TimeTable (Табельный_номер, Номер_пациента, Номер_кабинета,Дата, Время) values ('%1','%2','%3','%4','%5');").arg(dctN).arg(patN).arg(cabNmb).arg(dateZ).arg(time);
       mModel->setQuery(queryStr5);
     }

}

void MainWindow::patSearch(){
    Patients pat;
    pat.exec();

    //QString patN, dctN;

    QString patName=pat.PatientName();
    QString passport=pat.Passport();
    QString address=pat.Address();
    QString strahovk=pat.Strahovka();
    QString bornDate=pat.BornDate();
    bool pres=pat.Pres;
    QString Dat;
    ui->tableWidget_7->show();
    ui->frame_18->hide();

    if (pres){
        Dat = bornDate;
    }else {
        Dat = "";
    }


    QString filter_pat = "ФИО LIKE'"+patName+"%'";
    QString filter_born = "Дата_рождения LIKE'"+Dat+"'";
    QString filter_adrress = "Адрес LIKE'"+address+"%'";
    QString filter_passport = "Паспортные_данные LIKE'"+passport+"%'";
    QString filter_strahovk= "Номер_страхового_полиса LIKE'"+strahovk+"%'";

    QString text;
    if( patName.length() != 0 )
      text.append(filter_pat);

    if( passport.length() != 0 )
    {
      if( text.length() != 0 )
        text.append( " and " );
      text.append( filter_passport);
    }

    if( address.length() != 0 )
    {
      if( text.length() != 0 )
        text.append( " and " );
      text.append( filter_adrress );
    }

    if( strahovk.length() != 0 )
    {
      if( text.length() != 0 )
        text.append( " and " );
      text.append( filter_strahovk );
    }

    if( Dat.length() != 0 )
    {
      if( text.length() != 0 )
        text.append( " and " );
      text.append( filter_born );
    }

    if (text.length()!=0){
        int i=0;

        QString Name, Born, Adrs, Pasprt, NumStrah;
        const QString queryStr7 = QString::fromUtf8("Select ФИО, Дата_рождения, Адрес, Паспортые_данные, Номер_страхового_полиса from Patients where %1").arg(text);
        QSqlQuery selectt7;
        selectt7.exec(queryStr7);
        while(selectt7.next()){
        Name+= selectt7.value(0).toString()+"\n";
        Born+= selectt7.value(1).toString()+"\n";
        Adrs+= selectt7.value(2).toString()+"\n";
        Pasprt+= selectt7.value(3).toString()+"\n";
        NumStrah+= selectt7.value(4).toString()+"\n";
        i++;
        }
        int a=0, b=0, c=0 ,d=0, e=0;
        QString A, B, C, D, E;
        QFont fnt;
        fnt.setFamily("verdana");
        QString dctr, pat;
        ui->tableWidget_7->setRowCount(1);
        ui->tableWidget_7->setColumnCount(i);
        for (int col=0; col<i;col++){
        while (Name[a]!='\n') {
            A+=Name[a];
            a++;
        }
        while (Born[b]!='\n') {
            B+=Born[b];
            b++;
        }
        while (Adrs[c]!='\n') {
            C+=Adrs[c];
            c++;
        }
        while (Pasprt[d]!='\n') {
            D+=Pasprt[d];
            d++;
        }
        while (NumStrah[e]!='\n') {
            E+=NumStrah[e];
            e++;
        }



            ui->tableWidget_7->setItem(0, col, new QTableWidgetItem("Имя пациента:\n"+A+"\n\nДата рождения:\n"+B+"\n\nАдрес:\n"+C+"\n\nПаспортные данные:\n"+D+"\n\nНомер страхового полиса:\n"+E));
            ui->tableWidget_7->item(0,col)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_7->item(0,col)->setFont(fnt);

            A.clear();
            B.clear();
            C.clear();
            D.clear();
            E.clear();
             a++;
             b++;
             c++;
             e++;
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

void MainWindow::dctrSearch(){
    doctors dc;
    dc.exec();
    QString spe, specc;
    QString dcName=dc.Name();
    QString Speliality=dc.Speciality();

    ui->tableWidget_7->show();
    ui->frame_18->hide();


    const QString queryStr77 = QString::fromUtf8("Select Код_специальности from Specialities where Название like '%1%'").arg(Speliality);
    QSqlQuery selectt77;
    selectt77.exec(queryStr77);
    while(selectt77.next()){
    specc+= selectt77.value(0).toString();
    }

    QString filter_name = "ФИО LIKE'"+dcName+"%'";
    QString filter_spec = "Код_специальности LIKE'"+specc+"'";


    QString text;
    if( dcName.length() != 0 )
      text.append(filter_name);

    if( Speliality.length() != 0 )
    {
      if( text.length() != 0 )
        text.append( " and " );
      text.append( filter_spec);
    }

    if (text.length()!=0){
        int i=0;

        QString Name, Teleph, specil;
        const QString queryStr7 = QString::fromUtf8("Select ФИО, Телефон, Код_специальности from Doctors where %1").arg(text);
        QSqlQuery selectt7;
        selectt7.exec(queryStr7);
        while(selectt7.next()){
        Name+= selectt7.value(0).toString()+"\n";
        Teleph+=selectt7.value(1).toString()+"\n";
        specil+=selectt7.value(2).toString()+"\n";
        i++;
        }
        int a=0, b=0, c=0;
        QString A, B, C;
        QFont fnt;
        fnt.setFamily("verdana");
        QString dctr, pat;
        ui->tableWidget_7->setRowCount(1);
        ui->tableWidget_7->setColumnCount(i);
        for (int col=0; col<i;col++){
        while (Name[a]!='\n') {
            A+=Name[a];
            a++;
        }
        while (Teleph[b]!='\n') {
            B+=Teleph[b];
            b++;
        }
        while (specil[c]!='\n') {
            C+=specil[c];
            c++;
        }

        const QString queryStr4 = QString::fromUtf8("Select Название from Specialities where Код_специальности like '%1'").arg(C);
        QSqlQuery selectt4;
        selectt4.exec(queryStr4);
        while(selectt4.next()){
        spe+= selectt4.value(0).toString();
        }
            ui->tableWidget_7->setItem(0, col, new QTableWidgetItem("\nИмя врача:\n\n"+A+"\n\nТелефон:\n"+B+"\n\nСпециальность:\n"+spe+"\n"));
            ui->tableWidget_7->item(0,col)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_7->item(0,col)->setFont(fnt);

            A.clear();
            B.clear();
            C.clear();
            spe.clear();

             a++;
             b++;
             c++;

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


void MainWindow::on_action_5_triggered()
{
    ui->frame_18->hide();
    ui->frame_19->hide();
    ui->frame_20->hide();
    ui->frame_9->hide();
    ui->tableView->hide();
    ui->tableWidget_7->show();
    ui->tableWidget_7->horizontalHeader()->show();
    QString FIO, Telep, Spec;
    int i=0;
    const QString queryStr7 = QString::fromUtf8("Select ФИО, Телефон, Код_специальности from Doctors");
    QSqlQuery selectt7;
    selectt7.exec(queryStr7);
    while(selectt7.next()){
    FIO+= selectt7.value(0).toString()+"\n";
    Telep+=selectt7.value(1).toString()+"\n";
    Spec+=selectt7.value(2).toString()+"\n";
    i++;
    }
    QFont fnt;
    fnt.setFamily("verdana");
    QString Name, Tl, Sp,sspp;
    int a=0,b=1,c=0;
    ui->tableWidget_7->setRowCount(i);
    ui->tableWidget_7->setColumnCount(3);
    ui->tableWidget_7->setHorizontalHeaderItem(0,new QTableWidgetItem("ФИО врача"));
    ui->tableWidget_7->setHorizontalHeaderItem(1,new QTableWidgetItem("Телефон"));
    ui->tableWidget_7->setHorizontalHeaderItem(2,new QTableWidgetItem("Специальность"));

    ui->tableWidget_7->setShowGrid(false);
    for (int row = 0; row < i; row++){
        while (FIO[a]!='\n') {
            Name+=FIO[a];
            a++;
        }
        while (Telep[b]!='\n'&&Telep[b]!='\0') {
            Tl+=Telep[b];
            b++;
        }
        while (Spec[c]!='\n') {
            Sp+=Spec[c];
            c++;
        }
        const QString queryStr4 = QString::fromUtf8("Select Название from Specialities where Код_специальности like '%1'").arg(Sp);
        QSqlQuery selectt4;
        selectt4.exec(queryStr4);
        while(selectt4.next()){
        sspp+= selectt4.value(0).toString();
        }
        ui->tableWidget_7->setItem(row, 0, new QTableWidgetItem(Name));
        ui->tableWidget_7->setItem(row, 1, new QTableWidgetItem(Tl));
        ui->tableWidget_7->setItem(row, 2, new QTableWidgetItem(sspp));

        ui->tableWidget_7->item(row,0)->setTextAlignment(Qt::AlignCenter);
        //ui->tableWidget_7->item(row,0)->setFont(fnt);
        ui->tableWidget_7->item(row,1)->setTextAlignment(Qt::AlignCenter);
       // ui->tableWidget_7->item(row,1)->setFont(fnt);
        ui->tableWidget_7->item(row,2)->setTextAlignment(Qt::AlignCenter);
       // ui->tableWidget_7->item(row,2)->setFont(fnt);

        Name.clear();
        Tl.clear();
        Sp.clear();
        sspp.clear();

         a++;
         b++;
         c++;
    }
    ui->tableWidget_7->verticalHeader()->hide();
    ui->tableWidget_7->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget_7->resizeRowsToContents();
    ui->tableWidget_7->resizeColumnsToContents();
    ui->tableWidget_7->scrollToBottom();
    ui->tableWidget_7->setStyleSheet("QHeaderView::section { background-color:#fa7014 }");
   // ui->tableWidget_7->setStyleSheet("");
    ui->tableWidget_7->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void MainWindow::on_action_6_triggered()
{
    ui->frame_18->hide();
    ui->frame_19->hide();
    ui->frame_20->hide();
    ui->frame_9->hide();
    ui->tableView->show();
    ui->tableWidget_7->hide();
    mModel->setQuery("Select ФИО, дата_рождения, Адрес, Паспортые_данные, Номер_страхового_полиса from Patients");
    mModel->setHeaderData(0, Qt::Horizontal, "Имя пациента");
    mModel->setHeaderData(1, Qt::Horizontal, "Дата рождения");
    mModel->setHeaderData(2, Qt::Horizontal, "Адрес");
    mModel->setHeaderData(3, Qt::Horizontal, "Паспортные данные");
    mModel->setHeaderData(4, Qt::Horizontal, "Номер страхового полиса");
    ui->tableView->setShowGrid(false);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setStyleSheet("QHeaderView::section { background-color:#fa7014 }");
    ui->tableView->setModel(mModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_action_3_triggered()
{
    ui->frame_18->show();
    ui->frame_19->show();
    ui->frame_20->show();
    ui->frame_9->show();
    ui->tableView->hide();
    ui->tableWidget_7->hide();
}

void MainWindow::on_action_7_triggered()
{
    ui->frame_18->hide();
    ui->frame_19->hide();
    ui->frame_20->hide();
    ui->frame_9->hide();
    ui->tableView->show();
    ui->tableWidget_7->hide();
    mModel->setQuery("Select * from Cabinets");
    mModel->setHeaderData(0, Qt::Horizontal, "Номер кабинета");
    mModel->setHeaderData(1, Qt::Horizontal, "Количество рабочих мест");
    mModel->setHeaderData(2, Qt::Horizontal, "Этаж");
    ui->tableView->setShowGrid(false);

    ui->tableView->setStyleSheet("QHeaderView::section { background-color:#fa7014 }");

    ui->tableView->verticalHeader()->hide();
    ui->tableView->setModel(mModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_action_triggered()
{
    ui->frame_18->hide();
    ui->frame_19->hide();
    ui->frame_20->hide();
    ui->frame_9->hide();
    ui->tableView->show();
    ui->tableWidget_7->hide();
    mModel->setQuery("Select Название from Specialities");
    mModel->setHeaderData(0, Qt::Horizontal, "Название");
    ui->tableView->setShowGrid(false);
    ui->tableView->setStyleSheet("QHeaderView::section { background-color:#fa7014 }");
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setModel(mModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_action_12_triggered()
{
    ui->tableView->hide();
    ui->tableWidget_7->clear();

    patSearch();
    ui->tableWidget_7->setStyleSheet("QTableWidget:item\
    {\
    border-style: solid;\
      border-color: #fa7014;\
    border-radius:8px;\
    border-width:4px;\
    background:#fa7014;\
    }\
    QTableWidget\
    {\
    border-style: none;\
    }");
}

void MainWindow::on_action_13_triggered()
{
    ui->tableView->hide();
    ui->tableWidget_7->clear();

    dctrSearch();
    ui->tableWidget_7->setStyleSheet("QTableWidget:item\
    {\
    border-style: solid;\
      border-color: #fa7014;\
    border-radius:8px;\
    border-width:4px;\
    background:#fa7014;\
    }\
    QTableWidget\
    {\
    border-style: none;\
    }");
}
