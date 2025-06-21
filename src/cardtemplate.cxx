#include "editwindow.hxx"
#include "cardtemplate.hxx"
#include "ui_cardtemplate.h"

cardtemplate::cardtemplate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cardtemplate)
{
    ui->setupUi(this);
}

cardtemplate::~cardtemplate()
{
    delete ui;
}

void cardtemplate::on_EditBtn_clicked()
{
    editwindow *dialog = new editwindow(this);
    dialog->exec();
}

