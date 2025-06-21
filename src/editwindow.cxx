#include "editwindow.hxx"
#include "ui_editwindow.h"

editwindow::editwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editwindow)
{
    ui->setupUi(this);
}

editwindow::~editwindow()
{
    delete ui;
}
