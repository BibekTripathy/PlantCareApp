#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLayoutItem>
#include "cardtemplate.hxx"
#include "mainWindow.hxx"
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event){
	QMainWindow::showEvent(event);

    if (firstShow) {
        firstShow = false;
        secondwindow *dialog = new secondwindow(this);
        dialog->setModal(true);  
		if (dialog->exec() == QDialog::Accepted) {
			QString filePath = dialog->getFilePath();
			plants.fetchData(filePath.toStdString());
            loadCardsDynamically();
        }
    }
}

void MainWindow::loadCardsDynamically() {
    // Create a new grid layout
    QGridLayout* gridLayout = new QGridLayout();

    // Remove any old layout from the container
    if (ui->cardContainer->layout()) {
        QLayoutItem* item;
        while ((item = ui->cardContainer->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->cardContainer->layout();  // delete the old layout
    }

    // Set the new grid layout
    ui->cardContainer->setLayout(gridLayout);

    std::vector<Plants::plantData> plantList = plants.getAllPlants();

    int row = 0, col = 0;
    const int columns = 2;

    for (const Plants::plantData& plant : plantList) {
        cardtemplate* card = new cardtemplate(this, &plants);
        card->setPlantData(plant);
        gridLayout->addWidget(card, row, col);

        col++;
        if (col >= columns) {
            col = 0;
            row++;
        }
    }

    // Optional: spacing for better visuals
    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(10, 10, 10, 10);
}

