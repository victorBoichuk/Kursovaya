#ifndef DOCTORS_H
#define DOCTORS_H

#include <QDialog>

namespace Ui {
class doctors;
}

class doctors : public QDialog
{
    Q_OBJECT

public:
    explicit doctors(QWidget *parent = nullptr);
    ~doctors();
    QString Name();
    QString Speciality();
signals:
    void firstWindow();
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::doctors *ui;
};

#endif // DOCTORS_H
