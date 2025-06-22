#include "editwindow.hxx"
#include "cardtemplate.hxx"
#include "ui_cardtemplate.h"

cardtemplate::cardtemplate(QWidget *parent, Plants* plantDb) : QWidget(parent), ui(new Ui::cardtemplate), plantManager(plantDb) {
    ui->setupUi(this);
}

cardtemplate::~cardtemplate()
{
    delete ui;
}

void cardtemplate::on_EditBtn_clicked()
{
    Plants::plantData data;
    data.id = plantId;
    data.name = ui->PlantName->text();
    data.description = ui->DescLabel->text();
    data.healthStatus = ui->StatLabel->text();

    editwindow dialog(data, this);
    if (dialog.exec() == QDialog::Accepted) {
        Plants::plantData updated = dialog.getUpdatedData();

        // Step 1: update UI
        setPlantData(updated);

        // Step 2: update database
        if (plantManager) {
            plantManager->updatePlantData(updated);
        }
    }
}


void cardtemplate::setPlantData(const Plants::plantData& data) {
    plantId = data.id;
    ui->PlantName->setText(data.name);
    //ui->speciesLabel->setText(data.species);
    ui->DescLabel->setText(data.description);
    ui->StatLabel->setText(data.healthStatus);
}

int cardtemplate::getPlantId(){
    return plantId;
}