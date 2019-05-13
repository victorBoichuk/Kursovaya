#include "add.h"
#include "ui_add.h"

Add::Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);
    ui->doctor->setPlaceholderText("ФИО врача");
    ui->time->setPlaceholderText("Время записи");
    ui->address->setPlaceholderText("Адрес");
    ui->cabinet->setPlaceholderText("№ кабинета");
    ui->patient->setPlaceholderText("ФИО пациента");
    ui->passport->setPlaceholderText("Паспортные данные");
    ui->strahovk->setPlaceholderText("Номер страховки");

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->frame_20->hide();

}

Add::~Add()
{
    delete ui;
}

QString Add::Address(){
    return ui->address->text();
}

QString Add::NCabinet(){
    return ui->cabinet->text();
}

QString Add::Passport(){
    return ui->passport->text();
}

QString Add::Strahovka(){
    return ui->strahovk->text();
}

QString Add::DoctorName(){
    return ui->doctor->text();
}

QString Add::PatientName(){
    return ui->patient->text();
}

QString Add::BornDate(){
    return ui->dateEdit_2->text();
}

QString Add::DateZapisi(){
    return ui->dateEdit->text();
}

QString Add::Time(){
    return ui->time->text();
}

void Add::on_pushButton_3_clicked()
{
    this->close();
    emit firstWindow();
}


void Add::on_pushButton_4_clicked()
{
    this->close();
    emit firstWindow();
}

void Add::on_radioButton_2_clicked()
{
    New = false;
    ui->frame_20->hide();
}

void Add::on_radioButton_clicked()
{
    New = true;
    ui->frame_20->show();
}

