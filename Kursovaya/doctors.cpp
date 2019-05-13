#include "doctors.h"
#include "ui_doctors.h"

doctors::doctors(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::doctors)
{
    ui->setupUi(this);
    ui->name->setPlaceholderText("ФИО");
    ui->specialitiesN->setPlaceholderText("Специальность");
}

doctors::~doctors()
{
    delete ui;
}

QString doctors::Name(){
    return ui->name->text();
}

QString doctors::Speciality(){
    return ui->specialitiesN->text();
}
void doctors::on_pushButton_3_clicked()
{
    this->close();
    emit firstWindow();
}

void doctors::on_pushButton_4_clicked()
{
    this->close();
    emit firstWindow();
}
