#include "editwindow.hxx"
#include "cardtemplate.hxx"
#include <QMessageBox>
#include "ui_cardtemplate.h"

cardtemplate::cardtemplate(QWidget *parent, Plants* plantDb) : QWidget(parent), ui(new Ui::cardtemplate), plantManager(plantDb) {
    ui->setupUi(this);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setMinimumSize(280, 180);
}

cardtemplate::~cardtemplate()
{
    delete ui;
}

void cardtemplate::on_EditBtn_clicked()
{
    Plants::plantData data;
    data.id = plantId;

    QString fullName = ui->PlantName->text();
    int bracketIndex = fullName.indexOf(" (");
    QString cleanName = (bracketIndex != -1) ? fullName.left(bracketIndex) : fullName;

    data.name = cleanName;
    data.species = species;
    data.description = ui->DescLabel->text();
    data.healthStatus = ui->StatLabel->text();

    editwindow dialog(data, this);
    if (dialog.exec() == QDialog::Accepted) {
        Plants::plantData updated = dialog.getUpdatedData();

        setPlantData(updated);

        if (plantManager) {
            plantManager->updatePlantData(updated);
        }
    }
}


void cardtemplate::setPlantData(const Plants::plantData& data) {
    plantId = data.id;
    species = data.species;
    QString cleanName = data.name;
    int bracketIndex = cleanName.indexOf(" (");
    if (bracketIndex != -1) {
        cleanName = cleanName.left(bracketIndex);
    }
    ui->PlantName->setText(QString("%1 (%2)").arg(cleanName, data.species));
    ui->DescLabel->setText(data.description);
    ui->StatLabel->setText(data.healthStatus);
}

int cardtemplate::getPlantId(){
    return plantId;
}
void cardtemplate::on_DeleteBtn_clicked()
{
    if (!plantManager) return;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete Plant",
                                  "Are you sure you want to delete this plant?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (plantManager->deletePlantById(plantId)) {
            emit requestDeletion(this);
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete the plant from the database.");
        }
    }
}
