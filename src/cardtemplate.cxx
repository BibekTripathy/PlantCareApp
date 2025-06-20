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
