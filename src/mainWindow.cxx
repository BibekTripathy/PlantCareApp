#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QString>
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
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->cardContainer->layout());

    if (!layout) {
        qDebug() << "Error: No layout found in cardContainer!";
        return;
    }

    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    std::vector<Plants::plantData> plantList = plants.getAllPlants();

    for (const Plants::plantData& plant : plantList) {
        cardtemplate* card = new cardtemplate(this);
        card->setPlantData(plant);
        layout->addWidget(card);
    }
}
