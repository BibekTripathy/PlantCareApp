#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include "plant.hxx"
#include "mainWindow.hxx"
#include "ui_mainWindow.h"
#include "cardtemplate.hxx"

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
            loadCardsDynamically();
        }
    }
}

std::string MainWindow::getAddress() {
	return MainWindow::filePath;
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

    // Dummy card loop — replace with DB data later
    for (int i = 0; i < 10; ++i) {
        cardtemplate* card = new cardtemplate(this);
        layout->addWidget(card);
    }
}
