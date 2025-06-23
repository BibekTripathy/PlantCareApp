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
        secondwindow *dialog = new secondwindow(this);
        dialog->setModal(true);  
        
        if (dialog->exec() == QDialog::Accepted) {
            QString filePath = dialog->getFilePath();
            plants.fetchData(filePath.toStdString());

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
