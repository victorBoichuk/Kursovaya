#include "search.h"
#include "ui_search.h"
#include<QMessageBox>
#include <QSqlQueryModel>
#include<QSqlQuery>
#include <QDate>
#include <QTableWidget>
#include<QTableWidgetItem>


Search::Search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);

}

Search::~Search()
{
    delete ui;
}
