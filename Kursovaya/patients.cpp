#include "patients.h"
#include "ui_patients.h"

Patients::Patients(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Patients)
{
    ui->setupUi(this);
    ui->address->setPlaceholderText("Адрес");
    ui->passport->setPlaceholderText("Паспортные данные");
    ui->strahovk->setPlaceholderText("Номер страховки");
    ui->name->setPlaceholderText("Имя пациента");
}

Patients::~Patients()
{
    delete ui;
}

QString Patients::Address(){
    return ui->address->text();
}


QString Patients::Passport(){
    return ui->passport->text();
}

QString Patients::Strahovka(){
    return ui->strahovk->text();
}

QString Patients::PatientName(){
    return ui->name->text();
}

QString Patients::BornDate(){
    return ui->dateEdit->text();
}

void Patients::on_pushButton_3_clicked()
{
    this->close();
    emit firstWindow();
}

void Patients::on_pushButton_4_clicked()
{
    this->close();
    emit firstWindow();
}

void Patients::on_pushButton_6_clicked()
{
    Pres=true;
    ui->pushButton_6->hide();
}
