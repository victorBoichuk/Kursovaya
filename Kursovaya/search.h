#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class Search;
}

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = nullptr);
    ~Search();
    void serc();

signals:
    void firstWindow();
private:
    Ui::Search *ui;
};

#endif // SEARCH_H
