#include "editwindow.hxx"
#include "ui_editwindow.h"

editwindow::editwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editwindow)
{
    ui->setupUi(this);
}

editwindow::editwindow(const Plants::plantData& data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editwindow),
    plantData(data)
{
    ui->setupUi(this);

    // Pre-fill the fields with the existing data
    ui->PlantNameEdit->setText(data.name);
    ui->DescEdit->setPlainText(data.description);
    ui->HealthEdit->setText(data.healthStatus);
}

editwindow::~editwindow()
{
    delete ui;
}

void editwindow::on_cancelBtn_clicked()
{
    reject();
}

// Return the updated data to the caller
Plants::plantData editwindow::getUpdatedData() const {
    Plants::plantData updated = plantData;
    updated.name = ui->PlantNameEdit->text();
    updated.description = ui->DescEdit->toPlainText();
    updated.healthStatus = ui->HealthEdit->text();
    return updated;
}

void editwindow::on_SaveBtn_clicked()
{
    accept();
}

