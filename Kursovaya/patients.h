#ifndef PATIENTS_H
#define PATIENTS_H

#include <QDialog>

namespace Ui {
class Patients;
}

class Patients : public QDialog
{
    Q_OBJECT



public:
    explicit Patients(QWidget *parent = nullptr);
    ~Patients();
    QString PatientName();
    QString Address();
    QString Passport();
    QString Strahovka();
    QString BornDate();
    bool Pres=false;
signals:
    void firstWindow();
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::Patients *ui;
};

#endif // PATIENTS_H
