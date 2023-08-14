// DataTableWindow.cpp
#include "datatablewindow.h"
#include "ui_datatablewindow.h"

DataTableWindow::DataTableWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataTableWindow)
{
    ui->setupUi(this);



}

DataTableWindow::~DataTableWindow()
{
    delete ui;
}
