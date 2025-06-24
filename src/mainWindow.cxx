#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLayoutItem>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileInfo>
#include <QSettings>
#include "cardtemplate.hxx"
#include "mainWindow.hxx"
#include "secondWindow.hxx"
#include "editwindow.hxx"
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->scrollArea->setWidgetResizable(true);
    ui->cardContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);

    if (firstShow) {
        firstShow = false;

        QSettings settings("YourCompany", "PlantCareApp");
        QString filePath = settings.value("lastDatabase").toString();

        bool fileLoaded = false;

        if (!filePath.isEmpty()) {
            QFileInfo checkFile(filePath);
            if (checkFile.exists() && checkFile.isFile()) {
                plants.fetchData(filePath.toStdString());
                fileLoaded = true;
            }
        }

        if (!fileLoaded) {
            secondwindow* dialog = new secondwindow(this);
            dialog->setModal(true);

            if (dialog->exec() == QDialog::Accepted) {
                filePath = dialog->getFilePath();
                plants.fetchData(filePath.toStdString());

                settings.setValue("lastDatabase", filePath);
                fileLoaded = true;
            }
        }

        if (fileLoaded) {
            int containerWidth = ui->scrollArea->viewport()->width();
            int cardWidth = 300;
            int spacing = 20;
            int columns = std::max(1, containerWidth / (cardWidth + spacing));

            loadCardsDynamically(columns);
        }
    }
}


void MainWindow::loadCardsDynamically(int columns) {
    // Clean old layout
    if (gridLayout) {
        QLayoutItem* item;
        while ((item = gridLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete gridLayout;
    }

    gridLayout = new QGridLayout();
    ui->cardContainer->setLayout(gridLayout);

    std::vector<Plants::plantData> plantList = plants.getAllPlants();

    int row = 0, col = 0;
for (const auto& plant : plantList) {
    cardtemplate* card = new cardtemplate(this, &plants);
    card->setPlantData(plant);

    connect(card, &cardtemplate::requestDeletion, this, &MainWindow::handleCardDeletion);

    gridLayout->addWidget(card, row, col);

    col++;
    if (col >= columns) {
        col = 0;
        row++;
    }
}

    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(10, 10, 10, 10);
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);

    if (!ui->scrollArea || !ui->cardContainer) return;

    int containerWidth = ui->scrollArea->viewport()->width();
    int cardWidth = 300;
    int spacing = 20;

    int columns = std::max(1, containerWidth / (cardWidth + spacing));

    loadCardsDynamically(columns);
}

void MainWindow::handleCardDeletion(cardtemplate* card) {
    if (!card || !gridLayout) return;

    gridLayout->removeWidget(card);
    
    card->deleteLater();

    int containerWidth = ui->scrollArea->viewport()->width();
    int cardWidth = 300;
    int spacing = 20;
    int columns = std::max(1, containerWidth / (cardWidth + spacing));

    loadCardsDynamically(columns);
}

void MainWindow::on_actionNew_Plant_triggered()
{
    Plants::plantData newPlant;
    newPlant.id = -1;
    newPlant.name = "";
    newPlant.species = "";
    newPlant.description = "";
    newPlant.healthStatus = "";

    editwindow dialog(newPlant, this);
    if (dialog.exec() == QDialog::Accepted) {
        Plants::plantData addedPlant = dialog.getUpdatedData();

        if (plants.insertNewPlant(addedPlant)) {
            int containerWidth = ui->scrollArea->viewport()->width();
            int cardWidth = 300;
            int spacing = 20;
            int columns = std::max(1, containerWidth / (cardWidth + spacing));

            loadCardsDynamically(columns);
        } else {
            QMessageBox::warning(this, "Error", "Failed to add plant to database.");
        }
    }
}
void MainWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure you want to quit?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        qApp->quit();
    }
}


void MainWindow::on_actionUnhealthy_triggered()
{
    std::vector<Plants::plantData> unhealthyPlants = plants.getFilteredPlantsByHealth("unhealthy");

    if (unhealthyPlants.empty()) {
        QMessageBox::information(this, "Info", "No unhealthy plants found.");
        return;
    }

    // Remove old layout
    if (gridLayout) {
        QLayoutItem* item;
        while ((item = gridLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }

    int containerWidth = ui->scrollArea->viewport()->width();
    int cardWidth = 300;
    int spacing = 20;
    int columns = std::max(1, containerWidth / (cardWidth + spacing));

    int row = 0, col = 0;

    for (const auto& plant : unhealthyPlants) {
        cardtemplate* card = new cardtemplate(this, &plants);
        card->setPlantData(plant);
        connect(card, &cardtemplate::requestDeletion, this, &MainWindow::handleCardDeletion);
        gridLayout->addWidget(card, row, col);

        col++;
        if (col >= columns) {
            col = 0;
            row++;
        }
    }

    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(10, 10, 10, 10);
}


void MainWindow::on_actionHealthy_triggered()
{
    std::vector<Plants::plantData> healthyPlants = plants.getFilteredPlantsByHealth("healthy");

    if (healthyPlants.empty()) {
        QMessageBox::information(this, "Info", "No healthy plants found.");
        return;
    }

    // Remove old layout
    if (gridLayout) {
        QLayoutItem* item;
        while ((item = gridLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }

    int containerWidth = ui->scrollArea->viewport()->width();
    int cardWidth = 300;
    int spacing = 20;
    int columns = std::max(1, containerWidth / (cardWidth + spacing));

    int row = 0, col = 0;

    for (const auto& plant : healthyPlants) {
        cardtemplate* card = new cardtemplate(this, &plants);
        card->setPlantData(plant);
        connect(card, &cardtemplate::requestDeletion, this, &MainWindow::handleCardDeletion);
        gridLayout->addWidget(card, row, col);

        col++;
        if (col >= columns) {
            col = 0;
            row++;
        }
    }

    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(10, 10, 10, 10);
}


void MainWindow::on_actionFilter_by_Species_triggered()
{
    std::vector<std::string> speciesList = plants.getAllSpecies();

    if (speciesList.empty()) {
        QMessageBox::information(this, "No Species", "No species found in the database.");
        return;
    }

    QStringList speciesOptions;
    for (const std::string& s : speciesList) {
        speciesOptions << QString::fromStdString(s);
    }

    bool ok;
    QString selectedSpecies = QInputDialog::getItem(
        this,
        "Filter by Species",
        "Select a species:",
        speciesOptions,
        0,      // default index
        false,  // editable = false (not a combo input)
        &ok
    );

    if (!ok || selectedSpecies.isEmpty()) return;

    std::vector<Plants::plantData> filtered = plants.getFilteredPlantsBySpecies(selectedSpecies.toStdString());

    if (filtered.empty()) {
        QMessageBox::information(this, "No Results", "No plants found for species: " + selectedSpecies);
        return;
    }

    // Clear existing cards
    if (gridLayout) {
        QLayoutItem* item;
        while ((item = gridLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }

    int containerWidth = ui->scrollArea->viewport()->width();
    int cardWidth = 300;
    int spacing = 20;
    int columns = std::max(1, containerWidth / (cardWidth + spacing));

    int row = 0, col = 0;
    for (const auto& plant : filtered) {
        cardtemplate* card = new cardtemplate(this, &plants);
        card->setPlantData(plant);
        connect(card, &cardtemplate::requestDeletion, this, &MainWindow::handleCardDeletion);
        gridLayout->addWidget(card, row, col);

        col++;
        if (col >= columns) {
            col = 0;
            row++;
        }
    }

    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(10, 10, 10, 10);
}

void MainWindow::on_actionReset_Filters_triggered()
{
    int containerWidth = ui->scrollArea->viewport()->width();
    int cardWidth = 300;
    int spacing = 20;
    int columns = std::max(1, containerWidth / (cardWidth + spacing));

    loadCardsDynamically(columns);
}


void MainWindow::on_actionChange_create_database_triggered()
{
    secondwindow* dialog = new secondwindow(this);
    dialog->setModal(true);

    if (dialog->exec() == QDialog::Accepted) {
        QString filePath = dialog->getFilePath();

        if (filePath.isEmpty()) return;

        QFileInfo checkFile(filePath);
        if (!checkFile.exists() || !checkFile.isFile()) {
            QMessageBox::warning(this, "Invalid File", "The selected database file does not exist.");
            return;
        }

        // Fetch new database
        plants.fetchData(filePath.toStdString());

        // Update settings for persistence
        QSettings settings("YourCompany", "PlantCareApp");
        settings.setValue("lastDatabase", filePath);

        // Refresh the UI
        int containerWidth = ui->scrollArea->viewport()->width();
        int cardWidth = 300;
        int spacing = 20;
        int columns = std::max(1, containerWidth / (cardWidth + spacing));

        loadCardsDynamically(columns);
    }
}
