#ifndef ADD_H
#define ADD_H

#include <QDialog>

namespace Ui {
class Add;
}

class Add : public QDialog
{
    Q_OBJECT

public:
    explicit Add(QWidget *parent = nullptr);
    ~Add();
    QString PatientName();
    QString DoctorName();
    QString NCabinet();
    QString Address();
    QString Passport();
    QString Strahovka();
    QString DateZapisi();
    QString BornDate();
    QString Time();
    bool New = false;
signals:
    void firstWindow();
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::Add *ui;
};

#endif // ADD_H
